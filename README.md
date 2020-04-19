# Mydev Project

## Components
* Device Driver (mydev)
* Shared Library (libmydev)
* App for Test (test\_mydev)

## Functions
* read
* write
* ioctl
  * init
  * deinit
  * read
  * write
  * rdwr

## Call Structure
* App -> shared library -> device driver

## How to build

1. How to build device driver
> make

2. How to build shared library
> make lib

3. How to build test app
> make test

## How to clean

1. How to clean device driver
> make clean

2. How to clean shared library
> make libclean

3. How to clean test app
> make testclean

