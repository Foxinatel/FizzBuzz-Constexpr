# FizzBuzz-Constexpr
**Because who needs runtime anyways?**

When compiled with -O1 or higher, this implementation of FizzBuzz uses TMP to fold the output into a single string at compile time. This gives absolute minimal runtime overhead, as the only operation required is the printing of the string.
