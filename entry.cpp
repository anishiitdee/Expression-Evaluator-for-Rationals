/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #pragma once
#include "entry.h"
SymEntry::SymEntry() {
    key = "";
    val = nullptr;
    left = nullptr;
    right = nullptr;
}
SymEntry::SymEntry(string k, UnlimitedRational* v) {
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;
}
SymEntry::~SymEntry() {
    left=nullptr;
    right=nullptr;
   
}
