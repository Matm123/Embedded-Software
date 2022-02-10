#ifndef External_Interrupts_priv
#define External_Interrupts_priv


#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__; \
    void vector (void)

#endif
