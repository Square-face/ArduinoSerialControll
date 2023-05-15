/**A store for storing messages that are shown or has been shown for the user
 * 
 */

import { writable, type Writable } from "svelte/store"

export enum importance {INFO, WARNING, ERROR}

export interface message {
    title: string,          // the message title
    message: string,        // the display message
    timeout: number,        // the number of seconds to show the message for before automatically removing it
    showing: boolean,       // if the message is currently showing
    showed: boolean,        // if the message has been displayed
    importance: importance, // How important the message is
}

function createMessages() {
    const {subscribe, set, update}: Writable<message[]> = writable([])

    return {
        subscribe,
        createMessage: (title: string, message: string, timeout: number, importance: importance) => {
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
                    importance: importance
                })
                return messages
            })
        },
        removeMessage: (index: number) => {
            update(messages => {
                messages[index].showed = true
                messages[index].showing = false
                return messages
            })
        },
    }
}

export const messages = createMessages()