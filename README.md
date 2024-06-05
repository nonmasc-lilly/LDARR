# LDARR

A simple Dynamic array implementation in C.

The reason for LDARRS inception is that linked lists are in fact, slower than regular dynamic array (this is largely due to cache misses). *Especially*
with significant over allocation. LDARR allows the user to create dynamic arrays, push values, pop values, and set values to it. The LDARR
functions all work with void * allthough macros exist to eliminate the need for thought about those void pointers.

See [Bjarn Stroustrup](https://www.youtube.com/watch?v=YQs6IC-vgmo) on linked lists.


