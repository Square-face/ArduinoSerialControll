/**Get the sum of all numbers in a list
 * 
 * Takes an array of numbers and returns the sum
 * 
 * @param numbers Array of numbers
 * 
 * @returns The sum of the numbers array
 */
function sum(numbers: number[]): number {
    // store the sum of numbers array
    var total = 0;

    // calculate the sum of the numbers array
    for(var i = 0; i < numbers.length; i++) {
        total += numbers[i];
    }

    return total;
}

/**Average of a list of numbers
 * 
 * Takes an array of numbers and returns the average
 * 
 * @param numbers Array of numbers
 * 
 * @returns The average of the numbers array
 */
function average(numbers: number[]): number {
    // return the average of the numbers array
    return sum(numbers) / numbers.length;
}

export {
    average,
    sum
}