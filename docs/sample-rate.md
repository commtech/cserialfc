# Sample Rate

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

###### Operating Range
| Card Family | Range |
| ----------- | ----- |
| FSCC (16C950) | 4 - 16 |
| Async-335 (17D15X) | 8, 16 |
| Async-PCIe (17V35X) | 4, 8, 16 |


## Get
```c
int serialfc_get_sample_rate(serialfc_handle h, unsigned *rate)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current sample rate value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

unsigned rate;

serialfc_get_sample_rate(h, &rate);
```


## Set
```c
int serialfc_set_sample_rate(serialfc_handle h, unsigned rate)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int` | What sample rate you would like set |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_INVALID_PARAMETER` | 17001 | Invalid parameter |

###### Examples
```c
#include <serialfc.h>
...

serialfc_set_sample_rate(h, 16);
```


### Additional Resources
- Complete example: [`examples/sample-rate.c`](../examples/sample-rate.c)
