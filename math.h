int my_ceil(double x) {
    int num = (int)x;
    if(x == (double)num)
        return num;
    return num + 1;
}

int my_floor(double x) {
    int num = (int)x;
    if(x == (double)num)
        return num - 1;
    return num;
}