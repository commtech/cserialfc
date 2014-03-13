# External Transmit

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

###### Operating Range
| Card Family | Range |
| ----------- | ----- |
| FSCC (16C950) | 0 - 8191 |


## Get
```c
int serialfc_get_external_transmit(serialfc_handle h, unsigned *num_frames)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current external transmit value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

unsigned num_frames;

serialfc_get_echo_cancel(h, &num_frames);
```


## Enable
```c
int serialfc_enable_external_transmit(serialfc_handle h, unsigned num_frames)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int` | What external transmit value to set |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |
| `SERIALFC_INVALID_PARAMETER` | 17001 | Invalid parameter |

###### Examples
```c
#include <serialfc.h>
...

serialfc_enable_external_transmit(h, 4);
```


## Disable
```c
int serialfc_disable_external_transmit(serialfc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

serialfc_disable_external_transmit(h);
```


### Additional Resources
- Complete example: [`examples/external-transmit.c`](../examples/external-transmit.c)
