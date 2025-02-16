class ConfigStore {
  private hasWorkspaceFolderCapability: boolean;
  private hasDiagnosticRelatedInformationCapability: boolean;

  constructor() {
    this.hasWorkspaceFolderCapability = false;
    this.hasDiagnosticRelatedInformationCapability = false;
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

export const configStore = new ConfigStore();
