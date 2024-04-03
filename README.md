<!--  -->
<!-- Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb -->
<!--  -->

# Segregated-Free-Lists

This is a C project for my SDA course's homework, designed to simulate a
Segregated Free Lists data structure and perform operations on its nodes using
CLI command.

## About

This is my homework for my Data Structures and Algorithms course, that I took in
my second semester of university, in 2024. Its main goal is to accomodate myself
with implementing basic data structures like a doubly linked list and learn
about how to manipulate these data structures in order to create somewhat of a
more complex one.

The project facilitates having a heap-like memory management, where the size of
the data is prioritised. The main feature that it has is providing the
possibility of allocating blocks of data with different sizes to use and
writing or reading continuous ones. The SFL initialised blocks that have sizes
given in powers of 2, then, on request, it tries finding the best fitted block
that it can give to its user, such that the memory is used efficiently.

The operations that can be performed are listed here:

* [Initialise heap](#Initialising-a-heap)
* [Allocate a block](#Allocating-a-block)
* [Free a block](#Freeing-a-block)
* [Read](#Reading)
* [Write](#Writing)
* [Dump memory](#Dumping-memory)
* [Destroy the heap](#Destroying-the-heap)

### Initialising a heap

Create a new heap and allocate memory for the starting blocks.

Starting address must be bigger than `0x0`.

**Calling**
```sh
INIT_HEAP <heap_begin_address> <lists_number> <list_size> <should_reconstitute>
```

**Example**

*Input*
```sh
INIT_HEAP 0x1 4 256 0
```

### Allocating a block

Allocate an usable block of memory that can be written to or read from.

This allocates the best fitting block. If the size is less then the next bigger
block, it will break that one into 2 different block, returning one to the user.

**Calling**
```sh
MALLOC <size>
```

**Example**

*Input*
```sh
MALLOC 37
```

### Freeing a block

Free a block that is currently in use, at the given address.

If the `should_reconstitute` parameter is true, it will try reconstructing the
initial block that this one might have been taken from.

**Calling**
```sh
FREE <address>
```

**Example**

*Input*
```sh
FREE 0xbeb
```

### Reading

Read continuously `size` bytes from the already allocated blocks, starting from
the given `address`.

If the memory is not allocated correctly, the program performs a memory dump and
stops.

**Calling**
```sh
READ <address> <size>
```

**Example**

*Input*
```sh
READ 0xbeb 32
```

### Writing

Write continuously `size` bytes to the already allocated blocks, starting from
the given `address`. If the `data` is less than `size`, it writes only `data`.

If the memory is not allocated correctly, the program performs a memory dump and
stops.

**Calling**
```sh
WRITE <address> <data> <size>
```

**Example**

*Input*
```sh
WRITE 0xbeb "https://www.youtube.com/watch?v=dQw4w9WgXcQ" 100
```

### Dumping memory

Perform a memory dump. This will list all the information regarding the SFL.

**Calling**
```sh
DUMP_MEMORY
```

**Example**

*Input*
```sh
DUMP_MEMORY
```

*Output*
```sh

```

### Destroying the heap

Destroy all the allocated memory and stops the program.

**Calling**
```sh
DESTORY_HEAP
```

## What I have learnt

This project got me accomodated with writing a doubly linked list and developing
my programs faster.

I didn't really find anything else to be new here, hence I used my old command
interpreter, which I should be turning into a library, and other concepts.
I got kind of bored at the end so I started skipping some steps here and there,
but it was no problem because I alrdeady head a pretty decent base project. I
feel like I'm developing a standard way of writing my homeworks now.
