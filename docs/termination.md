# Termination

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.0.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |

###### Card Support
| Card Family | Supported |
| ----------- |:-----:|
| FSCC (16C950) | No |
| Async-335 (17D15X) | No |
| Async-PCIe (17V35X) | Yes |


## Get
```c
int serialfc_get_termination(serialfc_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current termination value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

unsigned status;

serialfc_get_termination(h, &status);
```


## Enable
```c
int serialfc_enable_termination(serialfc_handle h)
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

serialfc_enable_termination(h);
```


## Disable
```c
int serialfc_disable_termination(serialfc_handle h)
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

serialfc_disable_termination(h);
```


### Additional Resources
- Complete example: [`examples/termination.c`](../examples/termination.c)
