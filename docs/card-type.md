# Card Type

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.1.6 |
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
int serialfc_get_card_type(serialfc_handle h, unsigned *type)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `type` | `unsigned int *` | The card type |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```
#include <serialfc.h>
...

unsigned type;

serialfc_get_card_type(h, &type);
```


### Additional Resources
- Complete example: [`examples/card-type.c`](../examples/card-type.c)
