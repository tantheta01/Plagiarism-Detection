#!/bin/bash

ans=0;
ans2=0;
for filename in source_files/*; do
	IFS='/' read -r -a array <<<"$filename"
	python3 cleaning.py source_files/"${array[1]}" cleaned_source_code/"${array[1]}"
	wc -c source_files/"${array[1]}"
	wc -c cleaned_source_code/"${array[1]}"
done