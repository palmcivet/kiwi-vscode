import * as path from 'node:path';
import { glob } from 'glob';
import * as Mocha from 'mocha';

export async function run(): Promise<void> {
  // Create the mocha test
  const mocha = new Mocha({
    ui: 'tdd',
    color: true,
  });
  mocha.timeout(10000);

  const files = await glob('**.test.js', { cwd: __dirname });

  // Add files to the test suite
  files.forEach(f => mocha.addFile(path.resolve(__dirname, f)));

  try {
    // Run the mocha test
    await new Promise<void>((resolve, reject) => {
      mocha.run((failures) => {
        if (failures > 0) {
          reject(new Error(`${failures} tests failed.`));
        }
        else {
          resolve();
        }
      });
    });
  }
  catch (error) {
    console.error(error);
    throw error;
  }
}
