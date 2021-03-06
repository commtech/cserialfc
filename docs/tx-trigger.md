# TX Trigger Level

The TX FIFO trigger level generates an interrupt whenever the data level in the transmit FIFO falls below this preset trigger level.

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
| FSCC (16C950) | 0 - 127 |
| Async-335 (17D15X) | 0 - 64 |
| Async-PCIe (17V35X) | 0 - 255 |


## Get
```c
int serialfc_get_tx_trigger(serialfc_handle h, unsigned *level)
```

###### Examples
```c
#include <serialfc.h>
...

unsigned level;

serialfc_get_tx_trigger(h, &level);
```


## Set
```c
int serialfc_set_tx_trigger(serialfc_handle h, unsigned level)
```

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_INVALID_PARAMETER` | 17001 | Invalid parameter |

###### Examples
```c
#include <serialfc.h>
...

serialfc_set_tx_trigger(h, 64);
```


### Additional Resources
- Complete example: [`examples/tx-trigger.c`](../examples/tx-trigger.c)
