cat:
    echo "Building cat!"
    gcc cat.c -o cat
    echo "cat was built successfully!"

catdebug:
    echo "Building cat!"
    gcc cat.c -g -DMYDEBUG=42 -o mycatdebug
    echo "cat was built successfully!"

fail1:
    gcc doesnotexist.c

segfault:
    echo "int main(){int*segfault=0; *segfault=0;return 0;}" > badprog.c
    gcc badprog.c -o badprog
    ./badprog
