<?php

namespace Katas;

class FizzBuzz{

    public function print(int $n):string{
        if($n % 3 == 0){
            $fizzBuzz = 'Fizz';
        }

        if($n % 5 == 0){
            $fizzBuzz .= 'Buzz';
        }

        $fizzBuzz == '' ? (string)$n : $fizzBuzz;

        return $fizzBuzz;
    }
}



?>