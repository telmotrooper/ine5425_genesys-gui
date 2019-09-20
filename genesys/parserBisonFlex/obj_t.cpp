#include "obj_t.h"
#include <string>

obj_t::obj_t() {

}

obj_t::~obj_t() {

}

obj_t::obj_t(double v, std::string t) {
    valor = v;
    tipo = t;
    id = 0;
}

obj_t::obj_t(double v, std::string t, unsigned long uid) {
    valor = v;
    tipo = t;
    id = uid;
}
