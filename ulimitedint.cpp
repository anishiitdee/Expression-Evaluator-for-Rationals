// #pragma once
#include "ulimitedint.h"
#include<iostream>
int is_greater(int size1, int size2, int* arr1, int* arr2) {
    int i = size1 - 1;
    while (i > 0 && arr1[i] == 0) {
        i--;
    }
    size1 = i + 1;

    i = size2 - 1;
    while (i > 0 && arr2[i] == 0) {
        i--;
    }
    size2 = i + 1;
    if (size1 > size2) {
        return 1;
    }
    else if (size1 < size2) {
        return 2;
    }
    else {
        for (int i = size1 - 1; i >= 0; --i) {
            if (arr1[i] > arr2[i]) {
                return 1;
            }
            else if (arr1[i] < arr2[i]) {
                return 2;
            }
        }
    }
     return 0;
}

bool IsZero1(UnlimitedInt* z) {
        if (z->get_array()[z->get_size()-1]!= 0) {
            return false;
        }
    return true;
}
int compareAbs(UnlimitedInt* i1, UnlimitedInt* i2) {
    const int* int1 = i1->get_array();
    const int* int2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();

    if (size1 < size2) return -1;
    if (size1 > size2) return 1;

    for (int i = size1 - 1; i >= 0; --i) {
        if (int1[i] < int2[i]) return -1;
        if (int1[i] > int2[i]) return 1;
    }
    return 0;
}
UnlimitedInt* abs( UnlimitedInt* i1) {
    UnlimitedInt* absoluteValue = new UnlimitedInt(i1->get_array(),i1->get_size(),1,i1->get_size());

    return absoluteValue;
}

bool isLessThan(UnlimitedInt* i1,UnlimitedInt* i2) {
    if (i1->get_sign() < i2->get_sign()) {
        return true;
    } else if (i1->get_sign() > i2->get_sign()) {
        return false;
    }

    if (i1->get_sign() == 1) {
        if (i1->get_size() < i2->get_size()) {
            return true;
        } else if (i1->get_size() > i2->get_size()) {
            return false;
        }

        for (int i = i1->get_size() - 1; i >= 0; --i) {
            if (*(i1->get_array()+i)<*(i2->get_array()+i)) {
                return true;
            } else if (*(i1->get_array()+i)>*(i2->get_array()+i)) {
                return false;
            }
        }
    } else {
        return isLessThan(abs(i2),i1);
    }

    return false;
}
UnlimitedInt::UnlimitedInt() {
    size = 0;
    sign = 0;
    capacity = 0;
    unlimited_int = nullptr;
}

UnlimitedInt::UnlimitedInt(string s) {
   if (s.empty() || (s.size() == 1 && (s[0] == '+' || s[0] == '-'))) {
        size = 1;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
        sign = 0;
        return;
    }
    int startIndex = 0;
    if (s[0] == '-' || s[0] == '+') {
        sign = (s[0] == '-') ? -1 : 1;
        startIndex = 1;
    } else {
        sign = 1;
    }
    size = s.size() - startIndex;
    capacity = size;
    unlimited_int = new int[size];
    for (int i = 0; i < size; ++i) {
        unlimited_int[i] = s[startIndex + size - 1 - i] - '0';
    }
    while (size > 1 && unlimited_int[size - 1] == 0) {
        size--;
    }
}
UnlimitedInt::UnlimitedInt(int i) {
    if (i == 0) {
        size = 1;
        sign = 0;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
    } else {
        sign = (i < 0) ? -1 : 1;
        i = abs(i);
        int num = i;
        size = 0;
        while (num > 0) {
            num /= 10;
            size++;
        }
        capacity = size;
        unlimited_int = new int[capacity];
        for (int j = size - 1; j >= 0; --j) {
            unlimited_int[size-1-j] = i % 10;
            i /= 10;
        }
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    this->size = sz;
    this->sign = sgn;
    this->capacity = cap;
    this->unlimited_int = new int[cap];
    
    for (int i = 0; i < sz; ++i) {
        this->unlimited_int[i] = ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt() {
        delete[] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
      if (i1->sign != i2->sign) {
        if (i1->sign == 1) {
            return sub(i1,abs(i2));
        } else {
            if(isLessThan(abs(i1),abs(i2))){
                return sub(abs(i2), abs(i1));
            }
            return sub(i2, abs(i1));
        }
    }
    UnlimitedInt* result = new UnlimitedInt();
    result->sign = i1->sign;

    result->size = max(i1->size, i2->size) + 1;
    result->capacity = result->size;

    result->unlimited_int = new int[result->size]();

    int carry = 0;

    for (int i = 0; i < result->size; ++i) {
    int digit1, digit2;
    if (i < i1->size) {
        digit1 = i1->unlimited_int[i];
    } else {
        digit1 = 0;
    }
    if (i < i2->size) {
        digit2 = i2->unlimited_int[i];
    } else {
        digit2 = 0;
    }
    int sum = carry + digit1 + digit2;
    result->unlimited_int[i] = sum % 10;
    carry = sum / 10;
}


    if (carry > 0) {
        result->size++;
        result->unlimited_int[result->size - 1] = carry;
    }

    return result;
}


UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
       if (i1->sign != i2->sign) {
        if (i1->sign == 1) {
            return add(i1, abs(i2));
        } else {
            UnlimitedInt* result = add(abs(i1), i2);
            result->sign = -1;
            return result;
        }
    }
     if ((isLessThan(abs(i1),abs(i2)))) {
         if (i1->sign==-1 && i2->sign==-1){
             UnlimitedInt* result = sub(abs(i1), abs(i2));
        result->sign = -result->sign;
        return result;
         }
        UnlimitedInt* result = sub(abs(i2), abs(i1));
        result->sign = -result->sign;
        return result;
    }
        UnlimitedInt* sub = new UnlimitedInt();
    if (i1->sign == 1 && i2->sign == -1) {
        sub->sign = 1;
    } else if (i1->sign == -1 && i2->sign == 1) {
        sub->sign = -1;
    } else {
        if (i1->size > i2->size) {
            sub->sign = i1->sign;
        } else if (i1->size < i2->size) {
            sub->sign = -i2->sign;
        } else {
            int i = i1->size - 1;
            while (i >= 0 && i1->unlimited_int[i] == i2->unlimited_int[i]) {
                i--;
            }
            if (i < 0) {
                sub->sign = 1;
            } else if (i1->unlimited_int[i] > i2->unlimited_int[i]) {
                sub->sign = i1->sign;
            } else {
                sub->sign = -i2->sign;
            }
        }
    }
    int borrow = 0;
    sub->size = max(i1->size, i2->size);
    sub->capacity = sub->size;
    sub->unlimited_int = new int[sub->size];

    for (int i = 0; i < sub->size; ++i) {
        int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
        int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;

        int resultDigit = (digit1 - digit2 - borrow + 10) % 10;
        borrow = (digit1 - digit2 - borrow < 0) ? 1 : 0;

        sub->unlimited_int[sub->size - 1 - i] = resultDigit;
    }
    while (sub->size > 1 && sub->unlimited_int[0] == 0) {
        for (int i = 0; i < sub->size - 1; ++i) {
            sub->unlimited_int[i] = sub->unlimited_int[i + 1];
        }
        sub->size--;
    }
 int* reversedDigits = new int[sub->size];
    for (int i = 0; i < sub->size; ++i) {
        reversedDigits[i] = sub->unlimited_int[sub->size - 1 - i];
    }

    delete[] sub->unlimited_int; 
    sub->unlimited_int = reversedDigits;

    return sub;
}


UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* mul = new UnlimitedInt();
    mul->sign = i1->sign * i2->sign;
    mul->size = i1->size + i2->size;
    mul->capacity = mul->size;
    mul->unlimited_int = new int[mul->size]();

    for (int i = 0; i < i1->size; ++i) {
        int carry = 0;
        for (int j = 0; j < i2->size || carry; ++j) {
            long long cur = mul->unlimited_int[i + j] + i1->unlimited_int[i] * 1ll * (j < i2->size ? i2->unlimited_int[j] : 0) + carry;
            mul->unlimited_int[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    while (mul->size > 1 && mul->unlimited_int[mul->size - 1] == 0) {
        mul->size--;
    }
    return mul;
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    int* a = i1->get_array();
    int* b = i2->get_array();
    int i1_size = i1->get_size();
    int i2_size = i2->get_size();
    int i1_sign = i1->get_sign();
    int i2_sign = i2->get_sign();

    if (i1_sign == 0) {
        return new UnlimitedInt(0);
    }

    if (i1_size < i2_size) {
        if (i1_sign == i2_sign) {
            return new UnlimitedInt(0);
        } else {
            return new UnlimitedInt(-1);
        }
    }

    if (i2_size == 1 && b[0] == 1) {
        UnlimitedInt* res = new UnlimitedInt(i1->to_string());
        res->sign = i1_sign * i2_sign;
        return res;
    }

    int checker = is_greater(i1_size, i2_size, a, b);
    if (checker == 0) {
        if (i1_sign == i2_sign) {
            return new UnlimitedInt(1);
        } else {
            return new UnlimitedInt(-1);
        }
    }

    bool p1 = false;
    bool p2 = false;
    bool both = false;
    if (i1_sign == -1) {
        i1->sign = 1;
        p1 = true;
    }
    if (i2_sign == -1) {
        i2->sign = 1;
        p2 = true;
    }
    if (p1 && p2) {
        both = true;
    }

    UnlimitedInt* qt = new UnlimitedInt(0);
    UnlimitedInt* divi = new UnlimitedInt(0);
    UnlimitedInt* ten = new UnlimitedInt(10);
    UnlimitedInt* temp1;
    UnlimitedInt* temp2;

    for (int i = i1_size - 1; i >= 0; i--) {
        temp2 = new UnlimitedInt(divi->to_string());
        delete divi;
        divi = UnlimitedInt::mul(temp2, ten);
        delete temp2;

        temp1 = new UnlimitedInt(a[i]);
        temp2 = new UnlimitedInt(divi->to_string());
        delete divi;
        divi = UnlimitedInt::add(temp2, temp1);
        delete temp1;
        delete temp2;

        int q = 0;
        while (is_greater(divi->get_size(), i2_size, divi->get_array(), b) != 2) {
            temp2 = new UnlimitedInt(divi->to_string());
            delete divi;
            divi = UnlimitedInt::sub(temp2, i2);
            delete temp2;
            q++;
        }
        temp2 = new UnlimitedInt(qt->to_string());
        delete qt;
        qt = UnlimitedInt::mul(temp2, ten);
        delete temp2;
        temp1 = new UnlimitedInt(q);
        temp2 = new UnlimitedInt(qt->to_string());
        delete qt;
        qt = UnlimitedInt::add(temp2, temp1);
        delete temp1;
        delete temp2;
    }
    delete ten;
    if ((p1 || p2) && !both) {
        if ((divi->sign != 0)) {
            UnlimitedInt* ani = new UnlimitedInt(1);
            qt = UnlimitedInt::add(qt, ani);
            delete ani;
            qt->sign *= -1;
        } else {
            qt->sign *= -1;
        }
    }
    if (p1) {
        i1->sign = -1;
    }
    if (p2) {
        i2->sign = -1;
    }
    return qt;
}





UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* modResult;
    UnlimitedInt* quotient = div(i1, i2);  
    UnlimitedInt* product = mul(quotient, i2); 
    modResult = sub(i1, product); 
    delete quotient;
    delete product;
    return modResult;
}

string UnlimitedInt::to_string() {
    string str;
    if (sign == -1) {
        str = "-";
    }
    int i = size - 1;
    while (i >= 0 && unlimited_int[i] == 0) {
        --i;
    }
    if (i == -1) {
        return "0";
    }
    while (i >= 0) {
        str += std::to_string(unlimited_int[i]);
        --i;
    }
    return str;
}
// int main(){
//     UnlimitedInt i1("20338398933389");
//     UnlimitedInt i2("19393893");
    
//     // std::cout<<i1.get_array()[0];
//     UnlimitedInt* a= i1.div(&i1,&i2);
//     cout<<a->to_string()<<endl;
    
// }
