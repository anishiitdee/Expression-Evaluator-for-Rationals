/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #pragma once
#include "ulimitedrational.h"
bool iszero(UnlimitedInt* z) {
        if (z->get_array()[z->get_size()-1]!= 0) {
            return false;
        }
    
    return true;
}

UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b) {
    UnlimitedInt* x = new UnlimitedInt(a->get_array(), a->get_capacity(), 1, a->get_size());
    UnlimitedInt* y = new UnlimitedInt(b->get_array(), b->get_capacity(), 1, b->get_size());
    UnlimitedInt* difference = x->sub(x, y);
    if (difference->get_sign() != x->get_sign()) {
        UnlimitedInt* temp = y;
        y = x;
        x = temp;
    }
    delete difference;
    
    UnlimitedInt* remainder = UnlimitedInt::mod(x, y);
    while (!iszero(remainder)) {
        delete x;
        x = y;
        y = remainder;
        remainder = UnlimitedInt::mod(x, y);
    }
    delete x;
    delete remainder;
    return y;
}

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(1);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    p = num;
    q = den;
   
}
UnlimitedRational::~UnlimitedRational() {
    p=nullptr;
    q=nullptr;
}
UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}
UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}
string UnlimitedRational::get_p_str() {
    return p->to_string();
}
string UnlimitedRational::get_q_str() {
    return q->to_string();
}
string UnlimitedRational::get_frac_str() {
    return p->to_string() + "/" + q->to_string();
}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* new_num = UnlimitedInt::add(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i2->p, i1->q));
    UnlimitedInt* new_den = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedInt* new_num1 = UnlimitedInt::div(new_num,gcd(new_num,new_den));
    UnlimitedInt* new_den1 = UnlimitedInt::div(new_den,gcd(new_num,new_den));
    return new UnlimitedRational(new_num1, new_den1);
}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* new_num = UnlimitedInt::sub(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i2->p, i1->q));
    UnlimitedInt* new_den = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedInt* new_num1 = UnlimitedInt::div(new_num,gcd(new_num,new_den));
    UnlimitedInt* new_den1 = UnlimitedInt::div(new_den,gcd(new_num,new_den));
    return new UnlimitedRational(new_num1, new_den1);
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* new_num = UnlimitedInt::mul(i1->p, i2->p);
    UnlimitedInt* new_den = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedInt* z = gcd(new_num,new_den);
    UnlimitedInt* new_num1 = UnlimitedInt::div(new_num,z);
    UnlimitedInt* new_den1 = UnlimitedInt::div(new_den,z);
    return new UnlimitedRational(new_num1, new_den1);
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* new_num = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* new_den = UnlimitedInt::mul(i1->q, i2->p);
    UnlimitedInt* new_num1 = UnlimitedInt::div(new_num,gcd(new_num,new_den));
    UnlimitedInt* new_den1 = UnlimitedInt::div(new_den,gcd(new_num,new_den));
    return new UnlimitedRational(new_num1, new_den1);
}
// int main() {
//     UnlimitedInt* nonZeroNumber = new UnlimitedInt("14");
//     std::cout << "Is zero? " << (iszero(nonZeroNumber) ? "Yes" : "No") << std::endl;
//     delete nonZeroNumber;
//     UnlimitedInt* num1 = new UnlimitedInt(57);
//     UnlimitedInt* den1 = new UnlimitedInt(38);
//     UnlimitedRational* rational1 = new UnlimitedRational(num1, den1);
//     UnlimitedInt* gd= gcd(num1,den1);
//     cout<<gd->to_string()<<endl;
//     UnlimitedInt* num2 = new UnlimitedInt(5);
//     UnlimitedInt* den2 = new UnlimitedInt(6);
//     UnlimitedRational* rational2 = new UnlimitedRational(num2, den2);

//     // Add two rationals
//     UnlimitedRational* resultAdd = UnlimitedRational::add(rational1, rational2);
//     std::cout << "Addition: " << resultAdd->get_frac_str() << std::endl;

//     // Subtract two rationals
//     UnlimitedRational* resultSub = UnlimitedRational::sub(rational1, rational2);
//     std::cout << "Subtraction: " << resultSub->get_frac_str() << std::endl;
    
//     // Multiply two rationals
//     UnlimitedRational* resultMul = UnlimitedRational::mul(rational1, rational2);
//     std::cout << "Multiplication: " << resultMul->get_frac_str() << std::endl;

//     // Divide two rationals
//     UnlimitedRational* resultDiv = UnlimitedRational::div(rational1, rational2);
//     std::cout << "Division: " << resultDiv->get_frac_str() << std::endl;

//     // Clean up memory
//     delete num1;
//     delete den1;
//     delete rational1;

//     delete num2;
//     delete den2;
//     delete rational2;

//     delete resultAdd;
//     delete resultSub;
//     delete resultMul;
//     delete resultDiv;

//     return 0;
// }