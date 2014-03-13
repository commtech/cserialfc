# Read

Most users will want the advanced I/O capabilities included by using the Windows [OVERLAPPED I/O API](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx). We won't duplicate the documentation here, but for your reference, here is an [article](http://blogs.msdn.com/b/oldnewthing/archive/2011/02/02/10123392.aspx) on a common bug developers introduce while trying to cancel I/O operations when using OVERLAPPED I/O.

###### Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.0.0 |
| serialfc-linux | 2.0.0 |
| serialfc | 1.0.0 |


## Read
```c
int serialfc_read(fscc_handle h, char *buf, unsigned size, unsigned *bytes_read, OVERLAPPED *o)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc` | The handle to your port |
| `buf` | `char *` | The data buffer to hold incoming data |
| `size` | `unsigned` | The data buffer size |
| `bytes_read` | `unsigned *` | How many bytes were returned from the read |
| `o` | `OVERLAPPED *`| [Overlapped IO structure](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx) |

###### Examples
```c
#include <serialfc.h>
...

char idata[20] = {0};
unsigned bytes_read;

serialfc_read(h, idata, sizeof(idata), &bytes_read, NULL);
```

### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/serialfc.c`](../src/serialfc.c)
