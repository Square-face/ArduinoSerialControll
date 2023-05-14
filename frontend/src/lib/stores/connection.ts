import { writable } from "svelte/store";

// Get saved host from local storage or use the default fallback
export const host = writable(localStorage.host || 'localhost')
host.subscribe(value => localStorage.host = value)

// Get saved port from local storage or use the default fallback
export const port = writable(localStorage.port || '8080')
port.subscribe(value => localStorage.port = value)

export const ports = writable([])
export const serial = writable({
    open: false,
    port: null,
    baud: null,
    waiting: false,
})