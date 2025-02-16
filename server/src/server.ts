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
import { SchemaStore } from './service/store';

const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments(TextDocument);
const schemaStore = new SchemaStore(connection.console, documents);

setupOnInitialize(connection);
setupOnDidChangeContent(connection, documents);

setupOnCompletion(connection, schemaStore);
setupOnHover(connection, schemaStore);
setupOnReference(connection, schemaStore);
setupOnDefinition(connection, schemaStore);
setupOnDocumentSymbol(connection, schemaStore);
setupOnCodeAction(connection, schemaStore);

documents.listen(connection);
connection.listen();
