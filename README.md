# Manager
This is an effort to create a general purpose class to manage a few things.
```
ObjectManager.h : for Managing any objects for I/O purposes
GenArray.h      : to create and manage general purpose n-dimensional array
```

## ObjectManager
The motivation is to create a class to manage root objects (and anything else).
It utilizes the `void*` method.
- A static member function is given for getting the singleton (i.e `ObjectManager::Instance().GetObject()`).
- `SetGroup(dir,file)` creates a `dir` in `file` then attach the object in it.

## Use
```
mkdir build
cd build
cmake ..
make
cd ..
./Manager
```
