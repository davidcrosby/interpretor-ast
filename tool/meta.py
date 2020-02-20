import os

Expr_definitions = {
        "Assign"     : "Token name, Expr* value",
        "Binary"     : "Expr* left, Token op, Expr* right",
        "Call"       : "Expr* callee, Token paren, std::vector<Expr*> arguments",
        "Get"        : "Expr* object, Token name",
        "Grouping"   : "Expr* expression",
        "Literal"    : "std::any value",
        "Logical"    : "Expr* left, Token op, Expr* right",
        "Set"        : "Expr* object, Token name, Expr* value",
        "Super"      : "Token keyword, Token method",
        "This"       : "Token keyword",
        "Unary"      : "Token op, Expr* right",
        "Variable"   : "Token name"
        }

Stmt_definitions = {
        "Block"      : "std::vector<Stmt*> statements",
        "Class"      : "Token name, std::vector<Function> methods",
        "Class"      : "Token name, Variable superclass, std::vector<Function> methods",
        "Expression" : "Expr* expression",
        "Function"   : "Token name, std::vector<Token> params, std::vector<Stmt*> body",
        "If"         : "Expr* condition, Stmt* thenBranch, Stmt* elseBranch",
        "Print"      : "Expr* expression",
        "Return"     : "Token keyword, Expr* value",
        "Var"        : "Token name, Expr* initializer",
        "While"      : "Expr* condition, Stmt* body"
        }



input_classes = {
        "Expr": Expr_definitions,
        "Stmt": Stmt_definitions
        }

base_class_headers = {
        "Expr": ["token.h", "vector", "any"],
        "Stmt": ["token.h", "expr.h", "vector"]
        }


def define_sub_class(outfile, class_name, base_name):
    args = input_classes[base_name][class_name];
    args = [ arg for arg in args.split(',')]
    args = list(map(lambda l: list(filter(lambda x: x!="", l.split(" "))), args))
    outfile.write("class %s: public %s {\n" % (class_name, base_name));
    outfile.write("  private:\n");
    for entry in args:
        outfile.write("    %s %s;\n" % tuple(entry))
    outfile.write("  public:\n");

    constructor_arg_string, constructor_declaration_string = "", ""
    sp = ""
    for arg in args:
        constructor_arg_string += sp+"%s _%s" % tuple(arg)
        constructor_declaration_string += sp+"%s(_%s)" % (arg[1], arg[1])
        sp = ", "
    constructor_declaration_string += " {}"
    outfile.write("    %s( %s ): %s\n" % (class_name, constructor_arg_string,
        constructor_declaration_string))
    for arg in args: # getters
        typename, varname = arg
        varname = varname[0].upper() + varname[1:]
        outfile.write("    %s get%s() { return %s; }\n" % (typename, varname,
            varname))
    outfile.write("    void Accept(Abstract%sDispatcher dispatcher) override {\n" % base_name);
    outfile.write("      dispatcher.Dispatch(*this);\n");
    outfile.write("    }\n");
    outfile.write("};\n\n");


def define_abstract_dispatcher(outfile, base_name):
    outfile.write("class Abstract%sDispatcher {\n" % base_name);
    outfile.write("  public:\n");
    for class_name in input_classes[base_name]:
        outfile.write("    virtual void Dispatch(%s Expr) = 0;\n" % class_name);
    outfile.write("};\n");


def define_abstract_base_class(outfile, base_name):
    outfile.write("class %s {\n" % base_name);
    outfile.write("  public:\n");
    outfile.write("    virtual void Accept(Abstract%sDispatcher dispatcher) = 0;\n" % base_name)
    outfile.write("    virtual ~%s() = 0;\n" % base_name)
    outfile.write("};\n\n\n");
    outfile.write("\n\n");

def write_headers(outfile, base_name):
    for header in base_class_headers[base_name]:
        if ".h" in header:
            outfile.write('#include "%s"\n' % header)
        else:
            outfile.write("#include <%s>\n" % header)
    for lower_class in input_classes[base_name]:
        outfile.write("class %s;\n" % lower_class);

def generate_ast():
    for base_name in input_classes:
        outfile_name = "%s.h" % base_name
        with open(outfile_name.lower(), "w+") as f:
            f.write("#ifndef %s_HEADER_AUTO_GEN\n" % base_name)
            f.write("#define %s_HEADER_AUTO_GEN\n" % base_name)
            write_headers(f, base_name);
            define_abstract_dispatcher(f, base_name)
            define_abstract_base_class(f, base_name)
            defs = input_classes[base_name]
            for class_name in defs:
                define_sub_class(f, class_name, base_name)
            f.write("\n#endif")

if __name__ == "__main__":
    generate_ast();
