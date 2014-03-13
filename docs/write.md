# Write

###### Support
| Code | Version |
| ---  | ------- |
| serialfc-windows | 2.0.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |


## Write (Overlapped)
```c
int serialfc_write(fscc_handle h, char *buf, unsigned size, unsigned *bytes_written, OVERLAPPED *o)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `buf` | `char *` | The data buffer to transmit |
| `size` | `unsigned` | The number of bytes to transmit |
| `bytes_read` | `unsigned *` | How many bytes were written to the read |
| `o` | `OVERLAPPED *` | [Overlapped IO structure](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx) |

###### Examples
```c
#include <serialfc.h>
...

char odata[] = "Hello world!";
unsigned bytes_written;

serialfc_write(h, odata, sizeof(odata), &bytes_written, NULL);
```

### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/serialfc.c`](../src/serialfc.c)
