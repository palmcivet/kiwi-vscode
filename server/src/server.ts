import { TextDocument } from 'vscode-languageserver-textdocument';
import { createConnection, ProposedFeatures, TextDocuments } from 'vscode-languageserver/node';
import {
  setupOnCodeAction,
  setupOnCompletion,
  setupOnDefinition,
  setupOnDidChangeContent,
  setupOnDocumentSymbol,
  setupOnHover,
  setupOnInitialize,
  setupOnReference,
} from './service';

const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments(TextDocument);

setupOnInitialize(connection, documents);
setupOnDidChangeContent(connection, documents);
setupOnCompletion(connection, documents);
setupOnHover(connection, documents);
setupOnReference(connection, documents);
setupOnDefinition(connection, documents);
setupOnDocumentSymbol(connection, documents);
setupOnCodeAction(connection, documents);

documents.listen(connection);
connection.listen();
