#include <iostream>
#include <vector>
#include <string>

// Token types
enum TokenType {
    INT, ID, NUM, PLUS, MINUS, MULTIPLY, DIVIDE, GREATER, LESS, GREATER_EQUAL,
    LESS_EQUAL, EQUAL, NOT_EQUAL, SEMICOLON, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE,
    RIGHT_BRACE, IF, ELSE, WHILE, FOR, READ, WRITE, EOF_TOKEN, ASSIGN
};

// Token structure
struct Token {
    TokenType type;
    std::string lexeme;
};

class SyntaxAnalyzer {
public:
    SyntaxAnalyzer(const std::vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}

    void parse() {
        program();
        std::cout << "Syntax analysis completed successfully." << std::endl;
    }

private:
    void match(TokenType expectedType) {
        if (tokens[currentTokenIndex].type == expectedType) {
            currentTokenIndex++;
        } else {
            std::cerr << "Error: Expected token type " << expectedType << ", but found " << tokens[currentTokenIndex].type << std::endl;
            exit(1);
        }
    }

    void program() {
        match(LEFT_BRACE);
        declarationList();
        statementList();
        match(RIGHT_BRACE);
    }

    void declarationList() {
        while (tokens[currentTokenIndex].type == INT) {
            declarationStat();
        }
    }

    void declarationStat() {
        match(INT);
        match(ID);
        match(SEMICOLON);
    }

    void statementList() {
        while (tokens[currentTokenIndex].type != RIGHT_BRACE) {
            statement();
        }
    }

    void statement() {
        if (tokens[currentTokenIndex].type == IF) {
            ifStat();
        } else if (tokens[currentTokenIndex].type == WHILE) {
            whileStat();
        } else if (tokens[currentTokenIndex].type == FOR) {
            forStat();
        } else if (tokens[currentTokenIndex].type == READ) {
            readStat();
        } else if (tokens[currentTokenIndex].type == WRITE) {
            writeStat();
        } else if (tokens[currentTokenIndex].type == LEFT_BRACE) {
            compoundStat();
        } else if (tokens[currentTokenIndex].type == ID) {
            assignmentStat();
        } else {
            match(SEMICOLON); // Empty statement
        }
    }

    // Implement other functions for each non-terminal in the grammar

    void ifStat() {
        match(IF);
        match(LEFT_PAREN);
        boolExpression();
        match(RIGHT_PAREN);
        statement();
        if (tokens[currentTokenIndex].type == ELSE) {
            match(ELSE);
            statement();
        }
    }

    void whileStat() {
        match(WHILE);
        match(LEFT_PAREN);
        boolExpression();
        match(RIGHT_PAREN);
        statement();
    }

    void forStat() {
        match(FOR);
        match(LEFT_PAREN);
        assignmentExpression();
        match(SEMICOLON);
        boolExpression();
        match(SEMICOLON);
        assignmentExpression();
        match(RIGHT_PAREN);
        statement();
    }

    void writeStat() {
        match(WRITE);
        arithmeticExpression();
        match(SEMICOLON);
    }

    void readStat() {
        match(READ);
        match(ID);
        match(SEMICOLON);
    }

    void compoundStat() {
        match(LEFT_BRACE);
        statementList();
        match(RIGHT_BRACE);
    }

    void assignmentStat() {
        assignmentExpression();
        match(SEMICOLON);
    }

    void assignmentExpression() {
        match(ID);
        match(ASSIGN);
        arithmeticExpression();
    }

    void boolExpression() {
        
    }

    void arithmeticExpression() {
        term();
        while (tokens[currentTokenIndex].type == PLUS || tokens[currentTokenIndex].type == MINUS) {
            if (tokens[currentTokenIndex].type == PLUS) {
                match(PLUS);
            } else {
                match(MINUS);
            }
            term();
        }
    }

    void term() {
        
    }

    void factor() {
        
    }

private:
    const std::vector<Token>& tokens;
    size_t currentTokenIndex;
};

int main() {
    // Sample tokens (replace it with your actual token list)
    std::vector<Token> tokens = {
        {LEFT_BRACE, "{"}, {INT, "int"}, {ID, "x"}, {SEMICOLON, ";"}, {RIGHT_BRACE, "}"}, {EOF_TOKEN, ""}
    };

    SyntaxAnalyzer syntaxAnalyzer(tokens);
    syntaxAnalyzer.parse();

    return 0;
}
