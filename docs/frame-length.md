# Frame Length

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.1.5 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |

###### Card Support
| Card Family | Supported |
| ----------- |:-----:|
| FSCC (16C950) | Yes |
| Async-335 (17D15X) | No |
| Async-PCIe (17V35X) | No |

## Get
```c
int serialfc_get_frame_length(serialfc_handle h, unsigned *num_chars)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current frame length value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```
#include <serialfc.h>
...

unsigned num_chars;

serialfc_get_frame_length(h, &num_chars);
```


## Set
```c
int serialfc_set_frame_length(serialfc_handle h, unsigned num_chars)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int` | What frame length value to set |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |
| `SERIALFC_INVALID_PARAMETER` | 17001 | Invalid parameter |

###### Examples
```
#include <serialfc.h>
...

serialfc_set_frame_length(h, 4);
```


### Additional Resources
- Complete example: [`examples/frame-length.c`](../examples/frame-length.c)
