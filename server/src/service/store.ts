import type { Schema } from '../parser';

class ServerStore {
  private readonly files: Record<string, Schema>;

  private hasWorkspaceFolderCapability: boolean;
  private hasDiagnosticRelatedInformationCapability: boolean;

  constructor() {
    this.files = {};
    this.hasWorkspaceFolderCapability = false;
    this.hasDiagnosticRelatedInformationCapability = false;
  }

  public getFiles(): Record<string, Schema> {
    return this.files;
  }

  public setFile(uri: string, schema: Schema): void {
    this.files[uri] = schema;
  }

  public getFile(uri: string): Schema | undefined {
    return this.files[uri];
  }

  public setWorkspaceFolderCapability(value: boolean): void {
    this.hasWorkspaceFolderCapability = value;
  }

  public hasWorkspaceFolders(): boolean {
    return this.hasWorkspaceFolderCapability;
  }

  public setDiagnosticRelatedInformationCapability(value: boolean): void {
    this.hasDiagnosticRelatedInformationCapability = value;
  }

  public hasDiagnosticRelatedInformation(): boolean {
    return this.hasDiagnosticRelatedInformationCapability;
  }
}

export const store = new ServerStore();
