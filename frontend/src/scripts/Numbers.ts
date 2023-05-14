
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



/**Maps a value from one range to another
 * 
 * Takes a input value and input range and returns a output relative to how the input value is mapped to the input range
 * 
 * @param inMin Minimum input value
 * @param inMax Maximum input value
 * @param value Input value to be mapped
 * @param outMin Minimum output value
 * @param outMax Maximum output value
 * @returns Output value mapped relative to the input value
 */
function map(inMin: number, inMax: number, value: number, outMin: number, outMax: number): number {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}



export {
    average,
    sum,
    map
}