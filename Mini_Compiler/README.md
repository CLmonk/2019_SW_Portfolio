# Compiler in C

![01_agenda](01_figs/01_agenda.png)

## Purpose

![03_purpose](01_figs/03_purpose.png)

## Conditions

1. A variable type is an integer.
2. Only '+', '-' are used as operators.
3. There are two operands in a line.

![02_two_operand](01_figs/02_two_operand.png)

## 1. Lexical analyze / Scan

#### 1. 문자열(input-code)를 의미 있는 token으로 변환.

Input code

```c
main() {
    int a,b,c,d;
    
    a = 5;
    b = 3;
    c = 1;
    d = 4;
    
    a = b + c;
    d = b - c;
}
```

#### 2. Output : token, syntax_list.

First, store input-code in buffer[] except 'tab', 'enter'

![04_first_buf](01_figs/04_first_buf.png)

Second, store input-code in buffer[] except ';'  'space'  ','

![05_second_buf](01_figs/05_second_buf.png)

Then, I manage tokens with syntax_list after making tokens.

![06_syntax_list](01_figs/06_syntax_list.png)

Because it is easy for me to control tokens using the list.

## 2. Syntax analyzing

First, classify Variable / Operator like below.

![07_var_op](01_figs/07_var_op.png)

Manage variables in the linked list, and operators in the linear list. Operators are used for code generation, so I used the linear list for easy code generation.

#### Classify variables

![08_var](01_figs/08_var.png)

So, start index = start / end index = last

```c
for(cnt = start; cnt < last; cnt++){
    Add_list(L1, syntax_list[cnt]);
    for(_cnt = last; syntax_list[_cnt]; _cnt++){
        if(strcmp(syntax_list[cnt], syntax_list[_cnt]) == 0){
            (L1->last->usage)++;
        }
    }
}
```

There is a section to check the usage, which is to give priority.

It is so important to compile, because when the number of registers is fixed or there are many variables, the priority is determined and the registers are allocated.

So, if there are 16registers, 17th variable have to be stored on a memory.

But, there is a big Problem.

![09_problem](01_figs/09_problem.png)

So, registers are must be managed using optimization.

#### Classify Operator

![10_op](01_figs/10_op.png)



## 3. Code generation

We use the Operator list for Code generation.

![11_op(list)](01_figs/11_op(list).png)

#### MOV3

In assembly language, MOV3 means moving data from a register to another register.

![12_MOV3](01_figs/12_MOV3.png)

#### MOV4, ADD

I made assembler for two operations, so let's make codes for assembler.

ADD R0, R1, R2   ->  MOV4 R0, R1 + ADD R0, R2

![13_MOV4,ADD](01_figs/13_MOV4,ADD.png)

#### MOV4, SUB

It is same as the add code generation above.

![14_SUB](01_figs/14_SUB.png)

## 4. OUTPUT

You can see the output below.

![15_output](01_figs/15_output.png)

Then, look at the assembler and the decoder all together.

![16_out2](01_figs/16_out2.png)



