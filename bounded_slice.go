package main

import "fmt"

func bounded_slice(int [] input, int low, int high) []int {
	var int count = 0
	for i,v = range input {
		if (v > low && v < high) {
			count ++
		}
	}
	var output[] int = nil
	output = make([] int, count)
	var int index = 0
	for i,v = range input {
		if (v > low && v < high) {
			output[count] = v
			count ++
		}
	}
	return output
}

func main() {
	var slice[] int = nil
	slice = make([] int, count)
	nums := [4]int{3,9,-5,2}
	slice = nums[0:4]

}
