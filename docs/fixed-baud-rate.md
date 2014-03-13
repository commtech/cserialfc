# Fixed Baud Rate

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.3.0 |
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
int serialfc_get_fixed_baud_rate(serialfc_handle h, int *rate)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `int *` | The current fixed baud rate value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

int rate;

serialfc_get_fixed_baud_rate(h, &rate);
```


## Enable
```c
int serialfc_enable_fixed_baud_rate(serialfc_handle h, unsigned rate)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | What fixed baud rate to set |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

serialfc_enable_fixed_baud_rate(h, 9600);
```


## Disable
```c
int serialfc_disable_fixed_baud_rate(serialfc_handle h)
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

serialfc_disable_fixed_baud_rate(h);
```


### Additional Resources
- Complete example: [`examples/fixed-baud-rate.c`](../examples/fixed-baud-rate.c)
