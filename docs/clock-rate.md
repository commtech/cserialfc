# Clock Rate

###### Code Support
| Code | Version |
| -----| ------- |
| serialfc-windows | 2.1.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |

###### Card Support
| Card Family | Supported |
| ----------- |:-----:|
| FSCC (16C950) | Yes |
| Async-335 (17D15X) | Yes |
| Async-PCIe (17V35X) | Not required |


###### Operating Range
| Card Family | Range |
| ----------- | ----- |
| FSCC (16C950) | 200 Hz - 270 MHz |
| Async-335 (17D15X) | 6 Mhz - 180 Mhz |
| Async-PCIe (17V35X) | Not required |


## Set
```c
int serialfc_set_clock_rate(serialfc_handle h, unsigned rate)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `rate` | `unsigned` | The new clock frequency (Hz) |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |
| `SERIALFC_INVALID_PARAMETER` | 17001 | Invalid parameter |

###### Examples
Set the port's clock frequency to 18.432 MHz.
```
#include <serialfc.h>
...

serialfc_set_clock_rate(h, 18432000)
```


### Additional Resources
- Complete example: [`examples/clock-rate.c`](../examples/clock-rate.c)
