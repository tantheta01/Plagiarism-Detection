from api_app.serializers import (
    UserCreateSerializer, UserLoginSerializer, ChangePasswordSerializer
)
from rest_framework import generics, permissions
from django.contrib.auth.models import User
from django.contrib.auth.decorators import login_required
from django.http import FileResponse

from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework.status import HTTP_200_OK, HTTP_400_BAD_REQUEST

from rest_framework.authentication import TokenAuthentication
from rest_framework.permissions import IsAuthenticated

from .models import UploadFile
from django.core.files.storage import default_storage
from django.core.files.base import ContentFile

# from django.http import FileResponse
from rest_framework import viewsets, renderers
from rest_framework.decorators import action


from rest_framework.parsers import FormParser, MultiPartParser
from rest_framework import generics
from django.contrib.auth.forms import PasswordChangeForm
from django.contrib.auth import update_session_auth_hash
from django.shortcuts import render, redirect

import os
import time
import sys
import pandas as pd
sys.path.append('moss_winnowing')


# Importing the main logic functions
from driver import *



class UserCreate(generics.ListCreateAPIView):
    queryset = User.objects.all().order_by('pk')
    serializer_class = UserCreateSerializer


class UserLogin(APIView):
    permission_classes = [permissions.AllowAny]
    serializer_class = UserLoginSerializer

    def post(self, request, *args, **kwargs):
        data = request.data
        serializer = UserLoginSerializer(data=data)
        if serializer.is_valid(raise_exception=True):
            new_data = serializer.data
            return Response(new_data, status=HTTP_200_OK)
        return Response(serializer.errors, status=HTTP_400_BAD_REQUEST)




class FileUploadView(APIView):
    """The Upload File view should be availale to users only."""
    parser_classes = (MultiPartParser, FormParser)
    authentication_classes = (TokenAuthentication,)
    permission_classes = (IsAuthenticated, )

    def post(self, request, filename, format=None):
        print("Hello")
        file = request.data.get('file', None)
        if file:
            print("TATa")
            user = request.user
            uname = str(user.username)
            # tType = request.params.testType
            if uname not in os.listdir("api_app/media/"):
                os.mkdir("api_app/media/" + uname)
            
            # extention = filename.split(".")[1]

            # os.mkdir("api_app/media/" + uname + "/" + str(tType) + str(time.strftime("%Y%m%d-%H%M%S")) + "/")
            path = default_storage.save(
                "api_app/media/" + uname + "/" + filename, ContentFile(file.read()))
            
            uploadFile = UploadFile(path=path, user=user)
            uploadFile.save()
            


            file_path = "api_app/media/" + uname + "/" + filename
            extracted, fnames, csv_list, embeddings = extract_and_process(file_path)

            dirsize = len(os.listdir("api_app/media/" + uname))
            pd.DataFrame(csv_list).to_csv("api_app/media/" + uname + '/' + str(dirsize) + '.csv')
            
            # print(extracted['f2.py,f.py']['first_file'])
            print(csv_list)
            return Response({'data' : extracted, 'names' : fnames, 'csv' : pd.DataFrame(csv_list), 'embeddings' : embeddings}, HTTP_200_OK)
            # return Response({'data' : DiCtNAME}, HTTP_200_OK)
            # return Response({
            #     "path": path,
            #     "user": user.username
            # },
            #     status=HTTP_200_OK)
        return Response({"error": "file not found"}, status=HTTP_400_BAD_REQUEST)


class PassChangeView(generics.UpdateAPIView):
        """
        An endpoint for changing password.
        """
        serializer_class = ChangePasswordSerializer
        model = User
        authentication_classes = (TokenAuthentication,)
        permission_classes = (IsAuthenticated,)

        def get_object(self, queryset=None):
            obj = self.request.user
            return obj

        def update(self, request, *args, **kwargs):
            self.object = self.get_object()
            serializer = self.get_serializer(data=request.data)

            if serializer.is_valid():
                # Check old password
                if not self.object.check_password(serializer.data.get("old_password")):
                    return Response({"old_password": ["Wrong password."]}, status=status.HTTP_400_BAD_REQUEST)
                # set_password also hashes the password that the user will get
                self.object.set_password(serializer.data.get("new_password"))
                self.object.save()
                response = {
                    'status': 'success',
                    'code': HTTP_200_OK,
                    'message': 'Password updated successfully',
                    'data': []
                }

                return Response(response)

            return Response(serializer.errors, status=HTTP_400_BAD_REQUEST)

