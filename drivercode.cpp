#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "evaluator.h"

#define NUM_FILES 5

void checkEvalTreeBasic(ExprTreeNode *root, std::vector<std::string> &evalOutput, int &lineCount, bool &error){
    if(root == nullptr){
        error = true;
        std::cerr << "Eval tree isn't built correctly" << std::endl;
        return;
    }
    if(root->type == "VAR" || root->type == "VAL"){
        return;
    }
    checkEvalTreeBasic(root->left, evalOutput, lineCount, error);
    checkEvalTreeBasic(root->right, evalOutput, lineCount, error);

    cout<<evalOutput[lineCount]<<" output "<<root->evaluated_value->get_frac_str()<<endl;
    if(root->evaluated_value->get_frac_str() != evalOutput[lineCount]){
        error = true;
        // std::cerr<<"wrong output"<<evalOutput[lineCount]<<" "<<root->evaluated_value->get_frac_str()<<std::endl;
        std::cerr << "Eval tree isn't built correctly" << std::endl;
        return;
    }
    lineCount++;
}

void checkParseTreeBasic(ExprTreeNode *root, std::vector<std::string> &tokenVector, bool &error, bool isMainRoot = false){
    if(root == nullptr){
        error = true;
        std::cerr << "Parse tree isn't built correctly" << std::endl;
        return;
    }
    if(isMainRoot){
        if(root->left == nullptr || root->right == nullptr){
            error = true;
            std::cerr << "Parse tree isn't built correctly at node :=" << std::endl;
            return;
        }

        checkParseTreeBasic(root->left, tokenVector, error);
        tokenVector.push_back(":=");

        const bool needsParentheses = (root->right->type != "VAR" && root->right->type != "VAL");

        if (needsParentheses) {
            tokenVector.push_back("(");
        }

        checkParseTreeBasic(root->right, tokenVector, error);

        if (needsParentheses) {
            tokenVector.push_back(")");
        }

        return;
    }

    if(root->type == "VAR"){
        tokenVector.push_back(root->id);
        return;
    }
    if(root->type == "VAL"){
        tokenVector.push_back(root->val->get_p_str());
        return;
    }
    if(root->left == nullptr || root->right == nullptr){
        error = 1;
        std::cerr << "Parse tree isn't built correctly" << std::endl;
        return;
    }

    const bool needParanthesesLeft = (root->left->type != "VAR" && root->left->type != "VAL");

    if(needParanthesesLeft) {
        tokenVector.push_back("(");
    }

    checkParseTreeBasic(root->left, tokenVector, error);

    if(needParanthesesLeft) {
        tokenVector.push_back(")");
    }

    if (root->type == "ADD") {
        tokenVector.push_back("+");
    } else if (root->type == "SUB") {
        tokenVector.push_back("-");
    } else if (root->type == "MUL") {
        tokenVector.push_back("*");
    } else if (root->type == "DIV") {
        tokenVector.push_back("/");
    } else {
        error = 1;
        std::cerr << "Invalid type detected in the parse Tree, neither of VAR, VAL, ADD, SUB, MUL, DIV FOUND "<<root->type << std::endl;
        return; 
    }
    const bool needParanthesesRight = (root->right->type != "VAR" && root->right->type != "VAL");

    if(needParanthesesRight) {
        tokenVector.push_back("(");
    }

    checkParseTreeBasic(root->right, tokenVector, error);

    if(needParanthesesRight) {
        tokenVector.push_back(")");
    }

}


int main() {
    for(int  fileNum = 1; fileNum <= NUM_FILES; fileNum++) {
        Evaluator evaluator;
        std::string filePath = "./test_cases/test_" + std::to_string(fileNum) + ".txt";

        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            return 1;
        }

        
        std::string evalFilePath = "./test_cases/eval_output_" + std::to_string(fileNum) + ".txt";

        std::ifstream evalFile(evalFilePath);

        if (!evalFile.is_open()) {
            std::cerr << "Failed to open the file: " << evalFilePath << std::endl;
            return 1;
        }
        std::vector<std::string> evalOutput;
        std::string evalLine;
        while (std::getline(evalFile, evalLine)) {
            evalOutput.push_back(evalLine);
        }
        int evalCurr = 0;


        std::string line;
        std::regex tokenRegex("([a-zA-Z_][a-zA-Z0-9_]*|:=|\\(|\\)|\\+|\\-|\\*|\\/|\\d+)");
        int lineNum = 1;
        while (std::getline(inputFile, line)) {
            std::vector<std::string> tokens;
            auto words_begin = std::sregex_iterator(line.begin(), line.end(), tokenRegex);
            auto words_end = std::sregex_iterator();

            for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                tokens.push_back(i->str());
            }
            evaluator.parse(tokens);
            std::vector<std::string> tokenVector;
            bool parseError = false;
            checkParseTreeBasic(evaluator.expr_trees[evaluator.expr_trees.size() - 1], tokenVector, parseError, true);
            if(tokenVector != tokens || parseError){
                std::cerr << "Parse tree isn't built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
                return 1;
            }
            else{
                std::cout << "Parse tree built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
            }
            evaluator.eval();
            bool evalError = false;
            checkEvalTreeBasic(evaluator.expr_trees[evaluator.expr_trees.size() - 1]->right, evalOutput, evalCurr, evalError);
            if(evalError){
                std::cerr << "Eval tree isn't built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
                return 1;
            }
            else{
                std::cout << "Eval tree built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
            }
            lineNum++;
        }
        inputFile.close();

    }

    return 0;
}