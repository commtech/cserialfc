# Isochronous

If you apply an external clock to the card before turning on isochronous mode your system will freeze due to too many serial interrupts. Make sure and apply the clock after you are the  isochronous mode (so the interrupts are disabled).

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.1.1 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |

###### Card Support
| Card Family | Supported |
| ----------- |:-----:|
| FSCC (16C950) | Yes |
| Async-335 (17D15X) | No |
| Async-PCIe (17V35X) | No |

| Mode | Description |
| ----:| ----------- |
| 0 | Transmit using external RI# |
| 1 | Transmit using internal BRG |
| 2 | Receive using external DSR# |
| 3 | Transmit using external RI#, receive using external DSR# |
| 4 | Transmit using internal BRG, receive using external DSR# |
| 5 | Receive using internal BRG |
| 6 | Transmit using external RI#, receive using internal BRG |
| 7 | Transmit using internal BRG, receive using internal BRG |
| 8 | Transmit and receive using external RI# |
| 9 | Transmit clock is output on DTR# |
| 10 | Transmit clock is output on DTR#, receive using external DSR# |


## Get
```c
int serialfc_get_isochronous(serialfc_handle h, int *mode)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `int *` | The current mode value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

unsigned mode;

serialfc_get_isochronous(h, &mode);
```


## Enable
```c
int serialfc_enable_isochronous(serialfc_handle h, unsigned mode)
```

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |
| `SERIALFC_INVALID_PARAMETER` | 17001 | Invalid parameter |

###### Examples
```c
#include <serialfc.h>
...

serialfc_enable_isochronous(h, 7);
```


## Disable
```c
int serialfc_disable_isochronous(serialfc_handle h)
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

serialfc_disable_isochronous(h);
```


### Additional Resources
- Complete example: [`examples/isochronous.c`](../examples/isochronous.c)
