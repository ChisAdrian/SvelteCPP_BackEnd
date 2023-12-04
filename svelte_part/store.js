// store.js
import { writable } from 'svelte/store';

export const tableH = writable(['Col1_', 'Col2_']);
export const tableB = writable([
  ['Cel1_', 'Cel2'],
  ['Cel1', 'Cel2']
]);

// Example of using update
tableH.update(currentValue => ['UpdatedCol1', ...currentValue.slice(1)]);
