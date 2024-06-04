/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #pragma once
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode() {
    type = "";
    val = new UnlimitedRational(); 
    evaluated_value = nullptr;
    left = nullptr;
    right = nullptr;
    id="";
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
    type = t;
    val = new UnlimitedRational(v, new UnlimitedInt(1));
    evaluated_value = nullptr;
    left = nullptr;
    right = nullptr;
    id="";

}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    type = t;
    val = v;
    evaluated_value = nullptr;
    left = nullptr;
    right = nullptr;
    id="";
}

ExprTreeNode::~ExprTreeNode() {
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}