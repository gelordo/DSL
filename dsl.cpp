#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

enum TokenType {
    TOKEN_SAME,//1
    TOKEN_N_SAME,//2
    TOKEN_GREATER,//3
    TOKEN_SMALLER,//4
    TOKEN_INT,//5
    TOKEN_FLOAT,//6
    TOKEN_IDENTIFIER,//7
    TOKEN_END_LINE,//8
    TOKEN_START,//9
    TOKEN_END,//10
    TOKEN_L_BRACE,//11
    TOKEN_R_BRACE,//12
    TOKEN_SPACE,//13
    TOKEN_ADDITION,//14
    TOKEN_SUBTRACTION,//15
    TOKEN_MULTIPLICATION,//16
    TOKEN_DIVISION,//17
    TOKEN_EQUAL,//18
    TOKEN_INEQUALITY,//19
    TOKEN_IF,//20
    TOKEN_WHILE,//21
    TOKEN_INVALID,//22
    TOKEN_L_PAREN,//23
    TOKEN_R_PAREN,//24
    TOKEN_NUMBER,//25
    TOKEN_MINUS,//26
    TOKEN_PRINT//27
};

struct Token {
    TokenType type;
    string value;
};



vector<Token> tokenize(const string &input)
{

        vector<Token> tokens;
        size_t i = 0;
        while (i < input.length()) {
            if (isspace(input[i])) {
                i++;  // пропускаем пробелы
            }
            else if(input.substr(i, 1) == "\n")
            {
              i++;
            } 
        else if (input.substr(i, 3) == "add")
        {
            tokens.push_back({TOKEN_ADDITION, "add"});
            i += 3;
        } 
        
        else if (input.substr(i, 3) == "sub")
        {
            tokens.push_back({TOKEN_SUBTRACTION, "sub"});
            i += 3;
        }
        
        else if (input.substr(i, 4) == "mult")
        {
            tokens.push_back({TOKEN_MULTIPLICATION, "mult"});
            i += 4;
        }
        
        else if (input.substr(i, 3) == "div")
        {
            tokens.push_back({TOKEN_DIVISION, "div"});
            i += 3;
        }
        
        else if (input.substr(i, 2) == "if")
        {
            tokens.push_back({TOKEN_IF, "if"});
            i += 2;
        }
        
        else if (input.substr(i, 5) == "while")
        {
            tokens.push_back({TOKEN_WHILE, "while"});
            i += 5;
        }
        
        else if (input.substr(i, 1) == "{")
        {
            tokens.push_back({TOKEN_L_BRACE, "{"});
            i ++;
        }
        
        else if (input.substr(i, 1) == "}")
        {
            tokens.push_back({TOKEN_R_BRACE, "}"});
            i ++;
        }
        
        else if (input.substr(i, 5) == "start")
        {
            tokens.push_back({TOKEN_START, "start"});
            i += 5;
        }

        else if (input.substr(i, 4) == "init")
        {
            tokens.push_back({TOKEN_INT, "init"});
            i += 4;
        }
        
        else if (input.substr(i, 2) == "fl")
        {
            tokens.push_back({TOKEN_FLOAT, "fl"});
            i += 2;
        }
        
        else if (input.substr(i, 3) == "end")
        {
            tokens.push_back({TOKEN_END, "end"});
            i += 3;
        }
        
        else if (input.substr(i, 5) == "print")
        {
            tokens.push_back({TOKEN_PRINT, "print"});
            i += 5;
        }

        else if (input.substr(i, 1) == ";")
        {
            tokens.push_back({TOKEN_END_LINE, ";"});
            i += 1;
        }
        
        else if (input.substr(i, 2) == "==")
        {
            tokens.push_back({TOKEN_SAME, "=="});
            i += 2;
        }
        
        else if (input.substr(i, 2) == "!=")
        {
            tokens.push_back({TOKEN_N_SAME, "!="});
            i += 2;
        }
        
        else if (input.substr(i, 1) == ">")
        {
            tokens.push_back({TOKEN_GREATER, ">"});
            i ++;
        }
        
        else if (input.substr(i, 1) == "<")
        {
            tokens.push_back({TOKEN_SMALLER, "<"});
            i ++;
        }
        
        else if (input.substr(i, 1) == "=")
        {
            tokens.push_back({TOKEN_EQUAL, "="});
            i ++;
        }
        
        else if (input.substr(i, 1) == "(")
        {
            tokens.push_back({TOKEN_L_PAREN, "("});
            i ++;
        }

        else if (input.substr(i, 1) == ")")
        {
            tokens.push_back({TOKEN_R_PAREN, ")"});
            i ++;
        }

        else if (input.substr(i, 1) == "-")
        {
            tokens.push_back({TOKEN_MINUS, "-"});
            i ++;
        }

        else if (isalpha(input[i]))
        {
            size_t j = i;
            while (j < input.size() && (isalpha(input[j]) || input[j] == '_'))
            {
                j++;
            }
            tokens.push_back({TOKEN_IDENTIFIER, input.substr(i, j - i)});
            i = j;
        }
        else if (isdigit(input[i]))
        {
            size_t j = i;
            while (j < input.size() && (isdigit(input[j]) || input[j] == '.' ))//FIXME
            {
                j++;
            }
            tokens.push_back({TOKEN_NUMBER, input.substr(i, j - i)});
            i = j;
        }

         else
        {
            cerr << "Unknown character: " << input[i] << endl;
            system("pause");
            exit(1);
        }

        
}
return tokens;
}

string tokenTypeToString(TokenType type) {
  switch (type) {
  case TOKEN_INT:
    return "INT";
  case TOKEN_FLOAT:
    return "FLOAT";
  case TOKEN_ADDITION:
    return "ADDITION";
  case TOKEN_SUBTRACTION:
    return "SUBTRACTION";
  case TOKEN_MULTIPLICATION:
    return "MULTIPLICATION";  
  case TOKEN_DIVISION:
    return "DIVISION";
  case TOKEN_WHILE:
    return "WHILE";
  case TOKEN_IF:
    return "IF";
  case TOKEN_START:
    return "START";
  case TOKEN_END:
    return "END";
  case TOKEN_IDENTIFIER:
    return "IDENTIFIER";
  case TOKEN_EQUAL:
    return "EQUAL";
  case TOKEN_INEQUALITY:
    return "INEQUALITY";
  case TOKEN_SPACE:
    return "SPACE";
  case TOKEN_L_BRACE:
    return "L_BRACE";
  case TOKEN_R_BRACE:
    return "R_BRACE";
  case TOKEN_SAME:
    return "SAME";
  case TOKEN_END_LINE:
    return "END_LINE";
  case TOKEN_N_SAME:
    return "N_SAME";
  case TOKEN_GREATER:
    return "GREATER";
  case TOKEN_SMALLER:
    return "SMALLER";
  case TOKEN_L_PAREN:
    return "L_PAREN";
  case TOKEN_R_PAREN:
    return "R_PAREN";                      
  case TOKEN_INVALID:
    return "INVALID";
  case TOKEN_NUMBER:
    return "NUMBER"; 
  case TOKEN_PRINT:
    return "PRINT";  
  case TOKEN_MINUS:
    return "MINUS";     
  default:
    return "UNKNOWN";
  }
}

enum class BinaryOperator {
    TOKEN_ADDITION,
    TOKEN_SUBTRACTION,
    TOKEN_MULTIPLICATION,
    TOKEN_DIVISION,
    INVALID
    
};

enum TreeType {
BINARY_OP,
END_LINE,
init,
fl,
VARIABLE_DECLARATION,
VARIABLE,
VALUE,
VARIABLE_MODIFICATION,
START,
PRINT_OP
};

struct TreeNode { 
    TreeType type;
    string value;
    BinaryOperator binaryOperator;
    TreeNode* left;
    TreeNode* right;};

struct Variable
{
    string type;
    string varName;
    float value;
};

class Parser {
public:
    Parser(const vector<Token> &tokens);
    TreeNode *parse();
    

private:
    vector<Token>::const_iterator currentToken;
    vector<Token>::const_iterator endToken;
    bool wasMinusOperation = false;
    TreeNode *root;

    TreeNode *parseStatements();
    TreeNode *parseStatement();
    TreeNode *parseVariableDeclaration();
    TreeNode *parseVariableModification();
    TreeNode *parseExpression();
    TreeNode *parseTerm();
    TreeNode *parseFactor();
    TreeNode *parsePrint();
    TreeNode *createDisplayNode(TreeNode *variable);
    TreeNode *createBinaryOpNode(const string &op, TreeNode *left, TreeNode *right);
    TreeNode *createEndLineNode(const string &name);
    TreeNode *createVariableDeclarationNode(const string &type, const string &name, TreeNode *initialValue);
    TreeNode *createVariableNode(const string &name);
    TreeNode *createNumberNode(const string &num);
    TreeNode *createVariableModificationNode(const string &name, TreeNode *expression);
    //TreeNode *deleteTree(TreeNode* root);
    //TreeNode *createStartNode(const string &name);
};

Parser::Parser(const vector<Token> &tokens) {
    this->currentToken = tokens.begin();
    this->endToken = tokens.end();
    this->root = nullptr;
}

TreeNode *Parser::parse() {
    root = parseStatements();
    return root;
}

TreeNode *Parser::parseStatements(){
    TreeNode *statements = nullptr;
    if (currentToken->type == TOKEN_START){
        currentToken++;//FIXME
        while (currentToken->type != TOKEN_END ){
            TreeNode *statement = parseStatement();
            if (currentToken->type == TOKEN_END_LINE)
            {
            statements = createBinaryOpNode(";",createEndLineNode(";"),statement);
            currentToken++;
            }
            else
            {
                cerr << "Expected ';' at the end of the statement :" <<currentToken->value<< endl;
                system("pause");
                exit(1);
            }
        }
        
    } else {
        cerr << "Expected 'start' of the program" << endl;
        system("pause");
        exit(1);
    }
    return statements;
}

TreeNode *Parser::parseStatement(){
    if (currentToken->type == TOKEN_INT || currentToken->type == TOKEN_FLOAT)
    {
        return parseVariableDeclaration();
    }
    else if (currentToken->type == TOKEN_IDENTIFIER)
    {
        return parseVariableModification();
    }
    // else if (currentToken->type == TOKEN_WHILE)
    // {
    //     return parseWhileStatement();
    // }
    // else if (currentToken->type == TOKEN_IF)
    // {
    //     return parseIfStatement();
    // }
    else if (currentToken->type == TOKEN_PRINT)
    {
        return parsePrint();
    }
    
}

TreeNode *Parser::parseVariableModification()
{   
    string varName = currentToken->value;
    currentToken++;
    if (currentToken->type != TOKEN_EQUAL)
    {
        cerr << "Expected '=' after identificator" << endl;
        system("pause");
        exit(1);
    }
    else
    {
        currentToken++;
        TreeNode *initialvalue = parseExpression();
        return createVariableModificationNode(varName, initialvalue);
    }
}

TreeNode *Parser::parseExpression()
{
    TreeNode *left = parseTerm();
    if (currentToken->type == TOKEN_ADDITION || currentToken->type == TOKEN_SUBTRACTION)
    {
        wasMinusOperation = true;
        Token op = *currentToken;
        currentToken++;
        TreeNode *right = parseTerm();
        left = createBinaryOpNode(op.value, left, right);
    }
    wasMinusOperation = false;
    return left;
}

TreeNode *Parser::parseTerm()
{
    TreeNode *left = parseFactor();
    if (currentToken->type == TOKEN_MULTIPLICATION || currentToken->type == TOKEN_DIVISION)
    {
        wasMinusOperation = true;
        Token op = *currentToken;
        currentToken++;
        TreeNode *right = parseFactor();
        left = createBinaryOpNode(op.value, left, right);
    }
    wasMinusOperation = false;
    return left;
}

TreeNode *Parser::parseFactor()
{
    if (currentToken->type == TOKEN_NUMBER)
    {
        Token num = *currentToken;
        currentToken++;
        return createNumberNode(num.value);
    }
    else if (currentToken->type == TOKEN_NUMBER)
    {
        Token num = *currentToken;
        currentToken++;
        return createVariableNode(num.value);
    }
    else if (currentToken->type == TOKEN_L_PAREN)
    {
        currentToken++;
        TreeNode *expressionInParentheses = parseExpression();
        if (currentToken->type != TOKEN_R_PAREN)
        {
            cerr << "Expected closing parenthesis ')'" << endl;
            system("pause");
            exit(1);
        }
        currentToken++;
        return expressionInParentheses;
    }
    else
    {
        cerr << "Unexpected token: " << currentToken->value << endl;
        system("pause");
        exit(1);
    }

}

TreeNode *Parser::createVariableModificationNode(const string &name, TreeNode *expression)
{
    TreeNode *node = new TreeNode;
    node->type = VARIABLE_MODIFICATION;
    node->left = createVariableNode(name);
    node->right = expression;
    return node;

}
TreeNode *Parser::parseVariableDeclaration()
{
    string varName, type = currentToken->value;
    currentToken++;
    if (currentToken->type != TOKEN_IDENTIFIER){
        cerr << "Expected an identificator" << endl;
        system("pause");
        exit(1);
    }
    else{
        varName = currentToken->value;
        currentToken++;
        return createVariableDeclarationNode(type,varName,createNumberNode("0"));
    }
}
TreeNode *Parser::createVariableDeclarationNode(const string &type, const string &name, TreeNode *initialValue)
{
    TreeNode *node = new TreeNode;
    node->type = VARIABLE_DECLARATION;
    node->value = type;
    node->left = createVariableNode(name);
    node->right = initialValue;
    return node;
}

// TreeNode *Parser::deleteTree(TreeNode* root) {
//     if (root == nullptr) {
//         return;
//     }

//     deleteTree(root->left);
//     deleteTree(root->right);
//     delete root;
// }

TreeNode *Parser::createVariableNode(const string &name)
{
    TreeNode *node = new TreeNode;
    node->type = VARIABLE;
    node->value = name;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

TreeNode *Parser::createNumberNode(const string &num)
{
    TreeNode *node = new TreeNode;
    node->type = VALUE;
    node->value = num;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

TreeNode *Parser::createBinaryOpNode( const string &op, TreeNode *left, TreeNode *right)
{
    TreeNode *node = new TreeNode;
    node->type = BINARY_OP;
    node->value = op;
    node->left = left;
    node->right = right;
    return node;
}

TreeNode *Parser::createEndLineNode(const string &name)
{
    TreeNode *node = new TreeNode;
    node->type = END_LINE;
    node->value = name;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

TreeNode *Parser::parsePrint()
{
    currentToken++;
    if (currentToken->type != TOKEN_L_PAREN)
    {
        cerr << "Expected opening parenthesis '(' after display keyword." << endl;
        system("pause");
        exit(1);
    }
    currentToken++;
    if (currentToken->type != TOKEN_IDENTIFIER)
    {
        cerr << "Expected variable name in the display function." << endl;
        system("pause");
        exit(1);
    }
    string varName = currentToken->value;
    currentToken++;
    if (currentToken->type != TOKEN_R_PAREN)
    {
        cerr << "Expected closing parenthesis ')' after variable name in the display function." << endl;
        system("pause");
        exit(1);
    }
    currentToken++;
    return createDisplayNode(createVariableNode(varName));
}

TreeNode *Parser::createDisplayNode(TreeNode *variable)
{
    TreeNode *node = new TreeNode;
    node->type = PRINT_OP;
    node->value = variable->value;
    node->left = variable;
    node->right = nullptr;
    return node;
}

float evaluateTree(TreeNode* root) {
        if (root == nullptr) {
            return 0.0;
        }
}
class Variables
{
public:
    static void variableDeclaration(const string &type, const string &name, const float &value);
    static bool isVariableDeclared(const string &name);
    static float getVariableValue(const string &name);
    static string getVariableType(const string &name);
    static void showVariable(const string &name);
    static void enterScope();
    static void exitScope();

private:
    static vector<Variable> variables;
};

vector<Variable> Variables::variables;

void Variables::variableDeclaration(const string &type, const string &name, const float &value)
{
    for (auto &variable : variables)
        if (variable.varName == name)
        {
            variable.value = value;
            return;
        }
    variables.push_back({type, name, value});
}

bool Variables::isVariableDeclared(const string &name)
{
    for (const auto &variable : variables)
        if (variable.varName == name)
            return true;
    return false;
}

float Variables::getVariableValue(const string &name)
{
    for (const auto &variable : variables)
        if (variable.varName == name)
            return variable.value;
}

string Variables::getVariableType(const string &name)
{
    for (const auto &variable : variables)
        if (variable.varName == name)
            return variable.type;
}

void Variables::showVariable(const string &name)
{
    for (const auto &variable : variables)
        if (variable.varName == name)
        {
            cout << variable.value << endl;
        }
}

void Variables::enterScope()
{
    variables.push_back({});
}

void Variables::exitScope()
{
    auto it = find_if(Variables::variables.begin(), Variables::variables.end(), [](const Variable &variable)
                      { return variable.varName.empty(); });

    if (it != variables.end())
    {
        variables.erase(it, variables.end());
    }
}

bool checkString(const string &input)
{
    regex pattern("^BEGIN.*END$");

    if (regex_match(input, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Interpreter(const TreeNode *node) {
    if (node->type == BINARY_OP) {
        float leftValue = Interpreter(node->left);
        float rightValue = Interpreter(node->right);

        if (node->value == "add") {
            return leftValue + rightValue;
        } else if (node->value == "sub") {
            return leftValue - rightValue;
        } else if (node->value == "mult") {
            return leftValue * rightValue;
        } else if (node->value == "div") {
            if (rightValue == 0) {
                cerr << "Error: Division by zero." << endl;
                system("pause");
                exit(1);
            }
            return leftValue / rightValue;
        }

    } else if (node->type == VARIABLE_MODIFICATION) {
        string varName = node->left->value;
        if (Variables::isVariableDeclared(varName)) {
            float newValue = Interpreter(node->right);
            Variables::variableDeclaration(Variables::getVariableType(varName), varName, newValue);
        } else {
            cerr << "Переменная " << varName << " должна быть объявлена!" << endl;
            system("pause");
            exit(1);
        }
    } else if (node->type == PRINT_OP) {
        return Interpreter(node->left);
    } else if (node->type == VALUE) {
        return stof(node->value);
    }
}
int main() {
    string input = "start init x; x=5; print(x); end";
    vector<Token> tokens=tokenize(input);
    
    
    for (const auto& Token : tokens) {
        cout << "Type: " << tokenTypeToString(Token.type) << ", Value: " << Token.value <<endl;
    }
        Parser parser(tokens);
        TreeNode* root = parser.parse();
        double result = Interpreter(root);
        std::cout << "Result: " << result << std::endl;

    return 0;
}