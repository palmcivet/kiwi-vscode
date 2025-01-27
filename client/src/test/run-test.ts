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

  const testsRoot = __dirname;
  const files = await glob('**.test.js', { cwd: testsRoot });

  // Add files to the test suite
  files.forEach(f => mocha.addFile(path.resolve(testsRoot, f)));

  try {
    // Run the mocha test
    await new Promise<void>((resolve, reject) => {
      mocha.run((failures) => {
        if (failures > 0) {
          // eslint-disable-next-line prefer-promise-reject-errors
          reject(`${failures} tests failed.`);
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
