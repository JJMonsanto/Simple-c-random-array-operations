# Simple C Random Array Operations & Partitioning Pipeline

A modular C application that generates a 100-element pseudo-random integer array in the interval $[1, 999]$, applies conditional sign inversion for multiples of $3$ or $7$, and executes nine dedicated array-processing routines (`a` through `i`) covering row-aligned grid traversal, parity filtering, odd-index extraction, aggregate reduction, extremum index lookup, and positive/negative subarray partitioning.

---

## Specification Checklist (Problem 44)

| Requirement ID | Specification | Implemented Function | Status |
| :---: | :--- | :--- | :---: |
| **Build** | Generate 100 random numbers in the range `1 ... 999`; if evenly divisible by `3` or `7`, store as a negative number | `buildArray(int arr[], int size)` | `[x] Checked` |
| **Process a** | Print the array ten values to a line, with values aligned in rows | `printArray(int arr[], int size)` | `[x] Checked` |
| **Process b** | Print the odd values, ten to a line | `printOddValues(int arr[], int size)` | `[x] Checked` |
| **Process c** | Print the values at the odd-numbered index locations, ten to a line | `printOddIndexValues(int arr[], int size)` | `[x] Checked` |
| **Process d** | Return a count of the number of even values | `countEvenValues(int arr[], int size)` | `[x] Checked` |
| **Process e** | Return the sum of all values in the array | `sumArrayValues(int arr[], int size)` | `[x] Checked` |
| **Process f** | Return the location (index) of the smallest value in the array | `findSmallestLocation(int arr[], int size)` | `[x] Checked` |
| **Process g** | Return the location (index) of the largest value in the array | `findLargestLocation(int arr[], int size)` | `[x] Checked` |
| **Process h** | Copy all positive values to a new array, then use Process `a` to print the new array | `copyPositiveValues(int arr[], int size, int posArr[])` | `[x] Checked` |
| **Process i** | Copy all negative values to a new array, then use Process `a` to print the new array | `copyNegativeValues(int arr[], int size, int negArr[])` | `[x] Checked` |

---

## Architectural Pipeline

The program follows a modular pipeline architecture where `main(void)` seeds the pseudo-random number generator and coordinates each dedicated array operation:

```text
                                       [ main(void) ]
                                             |
                                             v
                                 [ Seed PRNG: srand(time) ]
                                             |
                                             v
                               [ buildArray(numbers, 100) ]
                         (1..999; negate if divisible by 3 or 7)
                                             |
       +------------------+------------------+------------------+------------------+
       |                  |                  |                  |                  |
       v                  v                  v                  v                  v
 [ Process a ]      [ Process b ]      [ Process c ]    [ Processes d..g ]  [ Processes h..i ]
  printArray        printOddValues   printOddIndexValues  countEvenValues   copyPositiveValues
 (10 per line)      (10 per line)     (indices 1,3..99)   sumArrayValues    copyNegativeValues
                                                          findSmallestLoc          |
                                                          findLargestLoc           v
                                                                            Reuse printArray
                                                                             (Process a)
```

---

## Mathematical & Algorithmic Formulation

### 1. Scaled Random Generation & Divisibility Rule
Each element $x_i$ ($0 \le i < 100$) is first sampled uniformly from $[1, 999]$:

$$r_i = \left(\text{rand}() \pmod{999}\right) + 1$$

If $r_i$ is evenly divisible by $3$ or $7$, it is stored as a negative integer:

$$x_i = \begin{cases} -r_i & \text{if } (r_i \bmod 3 = 0) \lor (r_i \bmod 7 = 0) \\ r_i & \text{otherwise} \end{cases}$$

### 2. Parity & Subarray Partitioning Invariants
- **Parity Conservation:** Every integer in the 100-element array is either odd (`arr[i] % 2 != 0`, printed in Process `b`) or even (`arr[i] % 2 == 0`, counted in Process `d`):
  $$N_{\text{odd}} + N_{\text{even}} = 100$$
- **Sign Partition Conservation:** Because the range $[1, 999]$ excludes zero, Process `h` ($x_i > 0$) and Process `i` ($x_i < 0$) partition the 100 elements into two disjoint subarrays:
  $$N_{\text{positive}} + N_{\text{negative}} = 100$$

---

## Empirical Verification & Test Matrix

Compiled with `gcc -Wall -Wextra -Werror` and verified across all invariants on a 100-element run:

| Verification Check | Expected Invariant | Empirical Run Result | Status |
| :--- | :--- | :--- | :---: |
| **Range & Divisibility Rule** | Every negative element is divisible by $3$ or $7$; every positive element is coprime to $3$ and $7$ | `40` negative values (all divisible by 3 or 7), `60` positive values | **PASS** |
| **Row Alignment (Process a)** | 10 columns per row formatted with `%6d` width alignment | `10` rows of `10` aligned values (`100` total) | **PASS** |
| **Parity Split (Processes b & d)** | $N_{\text{odd}} + N_{\text{even}} = 100$ | `50` odd values printed + `50` even values counted = `100` | **PASS** |
| **Odd Index Traversal (Process c)** | Visits indices $1, 3, 5, \dots, 99$ (50 elements, 5 rows of 10) | `50` elements printed across `5` aligned rows | **PASS** |
| **Extremum Locations (Processes f & g)** | Returns 0-based index of minimum and maximum array values | Smallest: `Index 3 (-966)` / Largest: `Index 73 (985)` | **PASS** |
| **Subarray Copy & Print (Processes h & i)** | $N_{\text{positive}} + N_{\text{negative}} = 100$, both printed via `printArray` | `60` positive (`6` rows) + `40` negative (`4` rows) = `100` | **PASS** |

---

## Compilation & Execution

### Using GCC (MinGW / Code::Blocks / Linux / macOS):
```bash
gcc -Wall -Wextra -Werror Simple-c-random-array-operations.c -o array_ops
./array_ops
```

### Sample Output:
```text
a. Complete Array (10 values per line, aligned in rows):
  -511  -427  -798  -966  -906   -87   341  -393  -371  -888
  -627    16   407   -36   727   367   577  -750   442   841
    88    32   128   734  -183   767  -240    92  -477    44
  -933    16   556   446   244  -633   356    -3  -957  -762
   272  -783   524   902  -690   577   901   761   298   487
   104   562  -273   -48  -321   736  -490   907  -387  -849
    68   691   890   754   979   268  -663    34   848   856
   569   923   265   985   128   565   536  -939   271  -801
   604   106  -399   535   646  -864   821   895   101   -28
  -930   -18   622  -864    31  -867  -501  -135   730   935

b. Odd Values in the Array (10 values per line):
  -511  -427   -87   341  -393  -371  -627   407   727   367
   577   841  -183   767  -477  -933  -633    -3  -957  -783
   577   901   761   487  -273  -321   907  -387  -849   691
   979  -663   569   923   265   985   565  -939   271  -801
  -399   535   821   895   101    31  -867  -501  -135   935

c. Values at Odd-Numbered Index Locations (10 values per line):
  -427  -966   -87  -393  -888    16   -36   367  -750   841
    32   734   767    92    44    16   446  -633    -3  -762
  -783   902   577   761   487   562   -48   736   907  -849
   691   754   268    34   856   923   985   565  -939  -801
   106   535  -864   895   -28   -18  -864  -867  -135   935

d. Count of Even Values:                     50
e. Sum of All Values in the Array:           8110
f. Location of Smallest Value:               Index 3 (Value: -966)
g. Location of Largest Value:                Index 73 (Value: 985)

h. Positive Values Copied to New Array (Printed via Process a):
   341    16   407   727   367   577   442   841    88    32
   128   734   767    92    44    16   556   446   244   356
   272   524   902   577   901   761   298   487   104   562
   736   907    68   691   890   754   979   268    34   848
   856   569   923   265   985   128   565   536   271   604
   106   535   646   821   895   101   622    31   730   935

i. Negative Values Copied to New Array (Printed via Process a):
  -511  -427  -798  -966  -906   -87  -393  -371  -888  -627
   -36  -750  -183  -240  -477  -933  -633    -3  -957  -762
  -783  -690  -273   -48  -321  -490  -387  -849  -663  -939
  -801  -399  -864   -28  -930   -18  -864  -867  -501  -135
```

---

## Static Safety Audit
- Unsafe unbounded calls (`gets`, bare `scanf("%s")`): **0 findings**
- Compiler diagnostics (`gcc -Wall -Wextra -Werror`): **0 warnings, 0 errors**
- Array bounds discipline: All index loops bounded strictly by `size` (`SIZE = 100`).
