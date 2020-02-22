import os

Expr_definitions = {
        "Assign"     : "Token name, Expr<R>* value",
        "Binary"     : "Expr<R>* left, Token op, Expr<R>* right",
        "Call"       : "Expr<R>* callee, Token paren, std::vector<Expr<R>*> arguments",
        "Get"        : "Expr<R>* object, Token name",
        "Grouping"   : "Expr<R>* expression",
        "Literal"    : "void* value, std::string actualType",
        "Logical"    : "Expr<R>* left, Token op, Expr<R>* right",
        "Set"        : "Expr<R>* object, Token name, Expr<R>* value",
        "Super"      : "Token keyword, Token method",
        "This"       : "Token keyword",
        "Unary"      : "Token op, Expr<R>* right",
        "Variable"   : "Token name"
        }

Stmt_definitions = {
        "Block"      : "std::vector<Stmt<R>*> statements",
        "Class"      : "Token name, std::vector<Function<R>> methods",
        "Class"      : "Token name, Variable<R> superclass, std::vector<Function<R>> methods",
        "Expression" : "Expr<R>* expression",
        "Function"   : "Token name, std::vector<Token> params, std::vector<Stmt<R>*> body",
        "If"         : "Expr<R>* condition, Stmt<R>* thenBranch, Stmt<R>* elseBranch",
        "Print"      : "Expr<R>* expression",
        "Return"     : "Token keyword, Expr<R>* value",
        "Var"        : "Token name, Expr<R>* initializer",
        "While"      : "Expr<R>* condition, Stmt<R>* body"
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
    outfile.write("template<class R>\n")
    outfile.write("class %s: public %s<R> {\n" % (class_name, base_name));
    outfile.write("  private:\n");
    for entry in args:
        outfile.write("    %s %s;\n" % tuple(entry))
    outfile.write("  public:\n");
    outfile.write("    ~%s();\n" % class_name);

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
        capped_varname = varname[0].upper() + varname[1:]
        outfile.write("    %s get%s() { return %s; }\n" % (typename, capped_varname,
            varname))
    outfile.write("    R Accept(Abstract%sDispatcher<R>* dispatcher) override {\n" % base_name);
    outfile.write("      return dispatcher->visit%s%s(*this);\n" % (class_name,
        base_name));
    outfile.write("    }\n");
    outfile.write("};\n\n");


def define_abstract_dispatcher(outfile, base_name):
    outfile.write("template<class R>\n")
    outfile.write("class Abstract%sDispatcher {\n" % base_name);
    outfile.write("  public:\n");
    for class_name in input_classes[base_name]:
        outfile.write("    virtual R visit%s%s(%s<R>& expr) = 0;\n"
                % (class_name, base_name, class_name));
    outfile.write("};\n");


def define_abstract_base_class(outfile, base_name):
    outfile.write("\ntemplate<class R>\n")
    outfile.write("class %s {\n" % base_name);
    outfile.write("  public:\n");
    outfile.write("    virtual R Accept(Abstract%sDispatcher<R>* dispatcher) = 0;\n" % base_name)
    outfile.write("    ~%s() {};\n" % base_name)
    outfile.write("};\n\n\n");
    outfile.write("\n\n");

def write_headers(outfile, base_name):
    for header in base_class_headers[base_name]:
        if ".h" in header:
            outfile.write('#include "%s"\n' % header)
        else:
            outfile.write("#include <%s>\n" % header)
    outfile.write("\n\n");
    for lower_class in input_classes[base_name]:
        outfile.write("\ntemplate<class R> ")
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
