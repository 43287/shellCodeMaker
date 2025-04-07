param (
    [string]$ProjectName
)

$scriptDir = Split-Path $MyInvocation.MyCommand.Path

$targetDir = Join-Path $scriptDir "x64\Release"

Set-Location -Path $targetDir

$exeName = "$ProjectName.exe"

if (Test-Path $exeName) {
    Write-Host "运行 $exeName ..."
    & ".\$exeName"

} else {
    Write-Host "错误：未找到文件 $exeName"
    exit 1
}
