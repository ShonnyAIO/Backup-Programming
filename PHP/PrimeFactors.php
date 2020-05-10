<?php
namespace Katas;

class PrimeFactors{
    public function generate(int $n){
        if($n < 1){
            throw new \Exception('Negatives not allowed'. $n);
        }
        $factors = [];
        $divisor = 2;
        while (n > 1){ 
            while ($n % $divisor == 0){
                $factors[] = $divisor;
                $n = $n/ $divisor;
            }
            $divisor++;
        }

        return $factors;
    }
        
}




?>