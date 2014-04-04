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

| Card Type | Value | Description |
| --------- | -----:| ----------- |
| `SERIALFC_CARD_TYPE_PCI` | 0 | Async-335 (17D15X) |
| `SERIALFC_CARD_TYPE_PCIE` | 1 | Async-PCIe (17V35X) |
| `SERIALFC_CARD_TYPE_FSCC` | 2 | FSCC (16C950) |
| `SERIALFC_CARD_TYPE_UNKNOWN` | 3 | Unknown |

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `type` | `unsigned int *` | The card type |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |

###### Examples
```c
#include <serialfc.h>
...

unsigned type;

serialfc_get_card_type(h, &type);
```


### Additional Resources
- Complete example: [`examples/card-type.c`](../examples/card-type.c)
