#!/usr/bin/perl
use strict;
use warnings;          
use diagnostics;        
use feature 'say';
use feature 'switch';
use v5.28;



# FILE
模式	描述
<   或 r	    只读方式打开，将文件指针指向文件头。
>   或 w	    写入方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
>>  或 a	    写入方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。
+<  或 r+	读写方式打开，将文件指针指向文件头。
+>  或 w+	读写方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
+>> 或 a+	读写方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。


my $emp_file = 'employees.txt';
open my $fh, '<', $emp_file 
	or die "Can't Open File: $_";
while (my $info = <$fh>) {
    chomp($info);
    my ($emp_name, $job, $id) = split /:/, $info;
    print "$emp_name is a $job and has the id $id \n";
}
close $fh or die "Couldn't Close File : $_";

open $fh, '>>', $emp_file 
	or die "Can't Open File : $_";  
print $fh "Mark:Salesman:124\n";
close $fh or die "Couldn't Close File : $_";


open $fh, '+<', $emp_file 
	or die "Can't Open File : $_";
seek $fh, 0, 0;
print $fh "Phil:Salesman:125\n";
close $fh or die "Can't Open File : $_";



    





