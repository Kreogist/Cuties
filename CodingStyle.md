Indentation
===========
4 spaces are used for indentation
Using **spaces** instead of using tabs

Declaring variables
===================
+ Suggest declaring each variable on a separate line
+ Avoid meaningless names (e.g. “a”, “rbarr”, “nughdeget”)
+ Single character variable names are only okay for counters and temporaries, where the purpose of the variable is obvious
+ Wait when declaring a variable until it is needed
+ Variables and functions start with a lower-case letter. Each consecutive word in a variable’s name starts with an upper-case letter
+ Avoid abbreviations
+ Classes always start with an upper-case letter. Public classes start with a ‘Q’ (QRgb) followed by an upper case letter. Public functions most often start with a ‘q’ (qRgb).
+ Acronyms are camel-cased (e.g. QXmlStreamReader, not QXMLStreamReader).

Whitespace
==========
+ Use blank lines to group statements together where suited
+ Always use only one blank line
+ For pointers or references, always use a single space between the type and ‘*’ or ‘&’, but no space between the ‘*’ or ‘&’ and the variable name.
+ No space after a cast
+ Avoid C-style casts when possible
        // Wrong
        char* blockOfMemory = (char* ) malloc(data.size());
           
        // Correct
        char *blockOfMemory = reinterpret_cast<char *>(malloc(data.size()));

+ Do not put multiple statements on one line. By extension, use a new line for the body of a control flow statement.

Parentheses
===========
+ Use parentheses to group expressions:
        // Wrong
        if (a && b || c)
           
        // Correct
        if ((a && b) || c)
           
        // Wrong
        a + b & c
           
        // Correct
        (a + b) & c

Switch statements
=================
+ The case labels are in the same column as the switch
+ Every case must have a break (or return) statement at the end or a comment to indicate that there’s intentionally no break, unless another case follows immediately.

            switch (myEnum)
            {
            case Value1:
                doSomething();
                break;
            case Value2:
            case Value3:
                doSomethingElse();
                // fall through
            default:
                defaultHandling();
                break;
            }

Jump statements (break, continue, return, and goto)
===================================================
+ Do not put ‘else’ after jump statements:

            // Wrong
            if (thisOrThat)
                return;
            else
                somethingElse();
     
            // Correct
            if (thisOrThat)
                return;
            somethingElse();

Line breaks
===========
+ Keep lines shorter than 100 characters; wrap if necessary
+ Operators go at the end of wrapped lines.
            if (longExpression +
                otherLongExpression +
                otherOtherLongExpression)
            {
            
            }


