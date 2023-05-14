/**A store for storing messages that are shown or has been shown for the user
 * 
 */

import { writable, type Writable } from "svelte/store"

export interface color {
    red: number,
    green: number,
    blue: number,
}

export interface message {
    title: string,      // the message title
    message: string,    // the display message
    timeout: number,    // the number of seconds to show the message for before automatically removing it
    showing: boolean,   // if the message is currently showing
    showed: boolean,    // if the message has been displayed
    color: color,       // what color to give the message
}

function createMessages() {
    const {subscribe, set, update}: Writable<message[]> = writable([])

    return {
        subscribe,
        createMessage: (title: string, message: string, timeout: number, color: color) => {
            /**Creating a new message and adding it to the list of messages
             * 
            */

            update(messages => {
                messages.push({
                    title: title, 
                    message: message,
                    timeout: timeout,
                    showing: false,
                    showed: false,
                    color: color
                })
                return messages
            })
        }
    }
}

export const messages = createMessages()