# Echo Cancel


###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.0.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |

###### Card Support
| Card Family | Supported |
| ----------- |:-----:|
| FSCC (16C950) | Yes |
| Async-335 (17D15X) | Yes |
| Async-PCIe (17V35X) | Yes |


## Get
```c
int serialfc_get_echo_cancel(serialfc_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current echo cancel value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

unsigned status;

serialfc_get_echo_cancel(h, &status);
```


## Enable
```c
int serialfc_enable_echo_cancel(serialfc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

serialfc_enable_echo_cancel(h);
```


## Disable
```c
int serialfc_disable_echo_cancel(serialfc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

serialfc_disable_echo_cancel(h);
```


### Additional Resources
- Complete example: [`examples/echo-cancel.c`](../examples/echo-cancel.c)
