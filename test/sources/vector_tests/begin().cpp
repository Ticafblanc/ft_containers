#include "../system/system_methods.ipp"
#include "__service.ipp"

template <typename T>
std::vector<int> begin_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    g_start1 = timer();
    typename std::vector<T>::iterator it = vector.begin();
    v.push_back(*it);
    v.push_back(*++it);
    g_end1 = timer();
    return v;
}

template <typename T>
std::vector<int> begin_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    g_start2 = timer();
    typename _vector<T>::iterator it = vector.begin();
    v.push_back(*it);
    v.push_back(*++it);
    g_end2 = timer();
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("begin()", begin_test, begin_test));
}