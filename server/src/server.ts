import {
  setupOnCodeAction,
  setupOnCompletion,
  setupOnDefinition,
  setupOnDidChangeContent,
  setupOnDocumentSymbol,
  setupOnHover,
  setupOnInitialize,
  setupOnReference,
} from '@server/service';
import { FileStore } from '@server/store';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { createConnection, ProposedFeatures, TextDocuments } from 'vscode-languageserver/node';
import { setupOnFormatting } from './service';

const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments(TextDocument);
const fileStore = new FileStore(connection.console, documents);

setupOnInitialize(connection);
setupOnDidChangeContent(connection, fileStore);

setupOnCompletion(connection, fileStore);
setupOnHover(connection, fileStore);
setupOnReference(connection, fileStore);
setupOnDefinition(connection, fileStore);
setupOnDocumentSymbol(connection, fileStore);
setupOnCodeAction(connection, fileStore);
setupOnFormatting(connection, fileStore);

documents.listen(connection);
connection.listen();
