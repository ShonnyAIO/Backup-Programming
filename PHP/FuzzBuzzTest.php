<?php

namespace Tests;

use Katas\FizzBuzz;
use PHPUnit\Framework\Testcase;

class FizzBuzzTest extends TestCase{

    public function testFizzBuzzWithNumberOne(){
        $fizzBuzz = new FizzBuzz();
        $this->assetSame( expected: '1', $fizzBuzz->print(n:1));

    }

    public function testFizzBuzzWithNumberTwo(){
        $fizzBuzz = new FizzBuzz();
        $this->assetSame( expected: '2', $fizzBuzz->print(n:2));

    }

    public function testFizzBuzzWithNumberThreeShouldReturn(){
        $fizzBuzz = new FizzBuzz();
        $this->assetSame( expected: 'Fizz', $fizzBuzz->print(n:3));

    }

    public function testFizzBuzzWithNumberSixShouldReturn(){
        $fizzBuzz = new FizzBuzz();
        $this->assetSame( expected: 'Fizz', $fizzBuzz->print(n:6));

    }

    public function testFizzBuzzWithNumberFiveShouldReturn(){
        $fizzBuzz = new FizzBuzz();
        $this->assetSame( expected: 'Buzz', $fizzBuzz->print(n:5));

    }

    public function testFizzBuzzWithNumber15ShouldReturn(){
        $fizzBuzz = new FizzBuzz();
        $this->assetSame( expected: 'Buzz', $fizzBuzz->print(n:15));

    }
}



?>