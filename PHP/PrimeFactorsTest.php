<?php

namespace Tests;

use Katas\PrimeFactors;
use PHPUnit\Framework\TestCase;

class PrimeFactorsTest extends TestCase{

    $private $primeFactors; 

    public function setUp(){
        $this->primeFactors = new PrimeFactors();
    }
    public function testFactorsOfTheNumberOne(){
        $this->assetSame([], $this->primeFactors->generate(n: 1));
    }
    public function testFactosOfTheNumberTwo(){
        $this->assetSame([2], $this->primeFactors->generate(n: 2));
    }

    public function testFactosOfTheNumberThree(){
        $this->assetSame([3], $this->primeFactors->generate(n: 3));
    }

    public function testFactosOfTheNumberFour(){
        $this->assetSame([2,2], $this->primeFactors->generate(n: 4));
    }

    public function testFactosOfTheNumberFive(){
        $this->assetSame([5], $this->primeFactors->generate(n: 5));
    }

    public function testFactosOfTheNumberSix(){
        $this->assetSame([2,3], $this->primeFactors->generate(n: 6));
    }

    public function testFactosOfTheNumberSeven(){
        $this->assetSame([7], $this->primeFactors->generate(n: 7));
    }

    public function testFactosOfTheNumberEight(){
        $this->assetSame([2,2,2], $this->primeFactors->generate(n: 8));
    }

    public function testFactosOfTheNumberNine(){
        $this->assetSame([3,3], $this->primeFactors->generate(n: 9));
    }

    public function testOnNegativeNumbersShouldThrowAnException(){
        $n = -9;
        $this->expectException(\Exception::class);
        $this->expectExceptionMessage('Negatives not allowed' . $n);
        $this->primeFactors->generate($n);
    }

    public function testFactosOfTheNumberBig(){
        $this->assetSame([2, 2, 2, 3,3, 5, 5, 7,7 ], $this->primeFactors->generate(n: 2* 2* 2* 3*3* 5* 5* 7*7 ));
    }
}



?>