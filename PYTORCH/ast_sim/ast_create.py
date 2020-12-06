import ast




class AnalysisNodeVisitor(ast.NodeVisitor):
    def visit_Import(self,node):
        print("node type is ", node._fields)
        ast.NodeVisitor.generic_visit(self, node)

    def visit_ImportFrom(self,node):
        print("Node type is this ", node._fields)
        ast.NodeVisitor.generic_visit(self, node)

    def visit_Assign(self,node):
        print('Node type: Assign and fields: ', node._fields, node.s)
        ast.NodeVisitor.generic_visit(self, node)
    
    def visit_BinOp(self, node):
        print('Node type: BinOp and fields: ', node._fields, node.s)
        ast.NodeVisitor.generic_visit(self, node)

    def visit_Expr(self, node):
        print('Node type: Expr and fields: ', node._fields)
        ast.NodeVisitor.generic_visit(self, node)

    def visit_Num(self,node):
        print('Node type: Num and fields: ', node._fields, node.s)

    def visit_Name(self,node):
        print('Node type: Name and fields: ', node._fields)
        ast.NodeVisitor.generic_visit(self, node)

    def visit_Str(self, node):
        print('Node type: Str and fields: ', node._fields, node.s)
        ast.NodeVisitor.generic_visit(self, node)



parsed = ast.parse("from pypi import sklearn \nprint('Hello World')")
v = AnalysisNodeVisitor()
v.visit(parsed)